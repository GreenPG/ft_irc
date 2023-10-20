/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:25:25 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/20 14:10:38 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bot.hpp"

int	Bot::initSocket() {
	struct addrinfo	hints;
	struct addrinfo	*servinfo;
	struct addrinfo	*p;
	std::string		port;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	std::cout << "Enter server port: ";
	std::cin >> port;
	if (getaddrinfo(NULL, port.c_str(), &hints, &servinfo) != 0) {
		std::cerr << "Error: getaddrinfo" << std::endl;
		freeaddrinfo(servinfo);
		return (1);
	}
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((this->_socketFd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			std::cerr << "Error: socket" << std::endl;
			continue;
		}
		if (connect(this->_socketFd, p->ai_addr, p->ai_addrlen) == -1) {
			close(this->_socketFd);
			continue;
		}
		break;
	} 
	if (p == NULL) {
		std::cerr << "Error: failed to connect" << std::endl;
		freeaddrinfo(servinfo);
		return (1);
	}
	freeaddrinfo(servinfo);
	return (this->_socketFd);
}

void	Bot::sendPass() const {
	std::string	password;
	std::string	response;
	int			size;

	std::cout << "Enter server password: ";
	std::cin >> password;
	size = 7 + password.size();
	send(this->_socketFd, PASS_QUERY(password).c_str(), size, 0);
}

int Bot::sendNickAndUser() const {
	std::string nick;
	std::string	response;
	int			size;
	int			nbytes;
	char		buf[256];

	memset(&buf, 0, 256);
	std::cout << "Enter Bot nickname: ";
	std::cin >> nick;
	size = 17 + nick.size();
	send(this->_socketFd, NICK_QUERY(nick).c_str(), size, 0);
	while(1) {
		if ((nbytes = recv(this->_socketFd, buf, sizeof(buf) - 1, 0)) <= 0) {
			std::cerr << "Error: recv" << std::endl;
			return (0);
		}
		response = buf;
		if (response.substr(0, 5) == ": 001") {
			std::cout << "The Bot is connected to the server" << std::endl;
			return (1);
		}
		else if (response.substr(0, 5) == ": 464") {
			std::cout << "Wrong password" << std::endl;
			sendPass();
			sendNickAndUser();
		}
		else  if (response.substr(0, 5) == ": 433") {
			std::cout << "Nickname already used. Enter another nickname :";
			std::cin >> nick;
			size = 7 + nick.size();
			send(this->_socketFd, NICK_QUERY(nick).c_str(), size, 0);
		}
	}
	return (0);
}

int Bot::loginToServ() const {
	sendPass();
	if (sendNickAndUser() == 0)
		return (1);
	std::cout << "Bot successfuly connected to the server" << std::endl;
	return (0);
}

int	Bot::readLoop() const {
	fd_set			master;
	fd_set			readFds;
	char			buf[256];
	int 			nbytes;
	bool			serverState;

	FD_ZERO(&master);
	FD_ZERO(&readFds);
	FD_SET(this->_socketFd, &master);
	serverState = true;
	while(serverState) {
		readFds = master;
		if (select(this->_socketFd + 1, &readFds, NULL, NULL, NULL) == -1) {
			std::cerr << "Error: select" << std::endl;
			close(this->_socketFd);
			return (1);
		}
		memset(buf, 0, sizeof(buf));
		if ((nbytes = recv(this->_socketFd, buf, sizeof(buf) - 1, 0) <= 0)) {
			if (nbytes < 0)
				std::cerr << "Error: receive" << std::endl;
			else 
				std::cerr << "Server has stopped. Stopping the Bot" << std::endl;
			close(this->_socketFd);
			return (1);
		}
		else {
			serverState = parser(buf);
		}
	}
	return (0);
}

bool	Bot::parser(std::string buf) const
{
	unsigned long	start;
	bool			state;
	
	state = true;
	if (buf == ":command to close the server\r\n") {
		std::cout << "Server was closed, stopping the Bot" << std::endl;
		close(this->_socketFd);
		return (false);
	}
	start = buf.find(" ", 0);
	start = buf.find_first_not_of(" ", start);
	if (buf.substr(start, 6) == "INVITE")
		invite(buf);
	if (buf.substr(start, 7) == "PRIVMSG")
		state = make_joke(buf);
	return (state);
}

void	Bot::invite(std::string msg) const
{
	std::string		chan;
	unsigned long	idx;

	idx = msg.find_last_of(" ");
	chan = msg.substr(idx, msg.size() - idx);
	sendMessage(JOIN_QUERY(chan).c_str());
}

void	Bot::killBot(std::string nick) const {
	sendMessage(KILL_MSG(nick).c_str());
	close(this->_socketFd);
	std::cout << "The Bot has been stopped by " << nick << std::endl;
}


bool	Bot::make_joke(std::string msg) const
{
	std::string	sender;
	std::string	target;

	msg.erase(msg.begin(), msg.begin() + 1);
	sender = msg.substr(0, msg.find(' '));
	msg.erase(msg.begin(),msg.begin() + msg.find(' ') + 1);
	msg.erase(msg.begin(),msg.begin() + msg.find(' ') + 1);
	target = msg.substr(0, msg.find(' '));
	msg.erase(msg.begin(),msg.begin() + msg.find(' ') + 1);
	if (msg[0] == ':')
		msg.erase(0, 1);
	if (msg == "!joke\n" || msg == "!joke\r\n") {
		if (target[0] == '#')
			send_random_joke(target);
		else
			send_random_joke(sender);
	}
	else if (msg == "!kill\r\n" || msg == "!kill\r\n"){
		killBot(sender);
		return (false);
	}
	else {
		std::cout << UNKNOWN_REPLY(sender) << std::endl;
		sendMessage(UNKNOWN_REPLY(sender).c_str());
	}
	return (true);
}

int	Bot::sendMessage(const char *message) const {
	int	messageSize;
	int	total;
	int	bytesleft;
	int	n;

	total = 0;
	messageSize = strlen(message);
	bytesleft = messageSize;
	while (total < messageSize) {
		n = send(this->_socketFd, message + total, bytesleft, 0);
		if (n == -1)
			break;
		total += n;
		bytesleft -=n;
	}

	if (n == -1)
		return (n);
	else
		return (total);
}


void	Bot::send_random_joke(std::string chan) const
{
	struct timeval				time;
	int							i;
	Bot							Bott;
	std::string					msg;

	gettimeofday(&time, NULL);
	i = time.tv_usec % 21 + 1;

	msg = get_start_message(chan);
	msg.append("hey ");
	msg.append(chan);
	msg.append("\r\n");
	sendMessage(msg.c_str());
	msg = get_start_message(chan);
	msg.append(Bott._tab[i].substr(0, Bott._tab[i].find('\n') + 1));
	sendMessage(msg.c_str());
	msg = get_start_message(chan);
	msg.append(Bott._tab[i].substr(Bott._tab[i].find('\n') + 1, Bott._tab[i].size()));
	sendMessage(msg.c_str());
}

std::string	Bot::get_start_message(std::string name) const
{
	std::string					msg;

	msg = "PRIVMSG";
	msg.append(" ");
	msg.append(name);
	msg.append(" ");
	return (msg);
}

Bot::Bot()
{
	std::string s;

	s = JOKE1();
	_tab.push_back(s);
	s = JOKE2();
	_tab.push_back(s);
	s = JOKE3();
	_tab.push_back(s);
	s = JOKE4();
	_tab.push_back(s);
	s = JOKE5();
	_tab.push_back(s);
	s = JOKE6();
	_tab.push_back(s);
	s = JOKE7();
	_tab.push_back(s);
	s = JOKE8();
	_tab.push_back(s);
	s = JOKE9();
	_tab.push_back(s);
	s = JOKE10();
	_tab.push_back(s);
	s = JOKE11();
	_tab.push_back(s);
	s = JOKE12();
	_tab.push_back(s);
	s = JOKE13();
	_tab.push_back(s);
	s = JOKE14();
	_tab.push_back(s);
	s = JOKE15();
	_tab.push_back(s);
	s = JOKE16();
	_tab.push_back(s);
	s = JOKE17();
	_tab.push_back(s);
	s = JOKE18();
	_tab.push_back(s);
	s = JOKE19();
	_tab.push_back(s);
	s = JOKE20();
	_tab.push_back(s);
	s = JOKE21();
	_tab.push_back(s);
	s = JOKE22();
	_tab.push_back(s);
}

Bot::~Bot()
{
}
