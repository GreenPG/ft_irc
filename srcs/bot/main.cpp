/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:14:27 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/19 17:30:27 by gpasquet         ###   ########.fr       */
/*   Updated: 2023/10/19 17:24:45 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>

#include "../../includes/joke_database.hpp"
#include "../../includes/bot.hpp"
#include <sys/time.h>
#include <vector>

void				parser(std::string buf, int fd);
void				invite(std::string msg, int fd);
static void			make_joke(std::string msg, int fd);
static void			send_random_joke(std::string chan, int fd);
static std::string	get_start_message(std::string name);
#define	NICK_QUERY(nick) ("NICK " + nick + "\r\nUSER bot\r\n")
#define	PASS_QUERY(pass) ("PASS " + pass + "\r\n")

int	initSocket() {
	struct addrinfo	hints;
	struct addrinfo	*servinfo;
	struct addrinfo	*p;
	int				socketFd;
	std::string		port;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	std::cout << "Enter server port: ";
	std::cin >> port;
	if (getaddrinfo(NULL, port.c_str(), &hints, &servinfo) != 0) {
		std::cerr << "Error: getaddrinfo" << std::endl;
		exit(1);
	}
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((socketFd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			std::cerr << "Error: socket" << std::endl;
			continue;
		}
		if (connect(socketFd, p->ai_addr, p->ai_addrlen) == -1) {
			close(socketFd);
			std::cerr << "Error: connect" << std::endl;
			continue;
		}
		break;
	} 
	if (p == NULL) {
		std::cerr << "Error: failed to connect" << std::endl;
		exit(1);
	}
	freeaddrinfo(servinfo);
	return (socketFd);
}

void	sendPass(int socketFd) {
	std::string	password;
	std::string	response;
	int			size;

	std::cout << "Enter server password: ";
	std::cin >> password;
	size = 7 + password.size();
	send(socketFd, PASS_QUERY(password).c_str(), size, 0);
}

int sendNickAndUser(int socketFd) {
	std::string nick;
	std::string	response;
	int			size;
	int			nbytes;
	char		buf[256];

	memset(&buf, 0, 256);
	std::cout << "Enter bot nickname: ";
	std::cin >> nick;
	size = 17 + nick.size();
	send(socketFd, NICK_QUERY(nick).c_str(), size, 0);
	while(1) {
		if ((nbytes = recv(socketFd, buf, sizeof(buf) - 1, 0)) <= 0) {
			std::cerr << "Error: recv" << std::endl;
			return (0);
		}
		response = buf;
		if (response.substr(0, 5) == ": 001") {
			std::cout << "The bot is connected to the server" << std::endl;
			return (1);
		}
		else if (response.substr(0, 5) == ": 464") {
			std::cout << "Wrong password" << std::endl;
			sendPass(socketFd);
			sendNickAndUser(socketFd);
		}
		else  if (response.substr(0, 5) == ": 433") {
			std::cout << "Nickname already used. Enter another nickname :";
			std::cin >> nick;
			size = 7 + nick.size();
			send(socketFd, NICK_QUERY(nick).c_str(), size, 0);
		}
	}
	return (0);
}

void loginToServ(int socketFd) {
	sendPass(socketFd);
	if (sendNickAndUser(socketFd) == 0)
		exit(1);
	std::cout << "Bot successfuly connected to the server" << std::endl;
}

void	readLoop(int socketFd) {
	fd_set			master;
	fd_set			readFds;
	char	buf[256];
	int nbytes;

	FD_ZERO(&master);
	FD_ZERO(&readFds);
	FD_SET(socketFd, &master);
	while(1) {
		readFds = master;
		if (select(socketFd + 1, &readFds, NULL, NULL, NULL) == -1) {
			std::cerr << "Error: select" << std::endl;
			close(socketFd);
			exit(1);
		}
		memset(buf, 0, sizeof(buf));
		if ((nbytes = recv(socketFd, buf, sizeof(buf) - 1, 0) <= 0)) {
			std::cerr << "Error: receive" << std::endl;
			exit(1);
		}
		else {
			parser(buf, socketFd);
		std::cout << buf;
		}
	}
}

void	parser(std::string buf, int fd)
{
	if (buf.substr(0, 7) == "INVITE ")
		invite(buf, fd);
	if (buf.substr(0, 9) == "PRIVMSG ")
		make_joke(buf, fd);
}

//:USER INVITE bot #CHAN
void	invite(std::string msg, int fd)
{
	msg.erase(msg.begin(), msg.begin() + msg.find(' ') + 1);
	std::cout << "t" << msg << "t\r\n" << std::endl;
	(void)msg;
	(void)fd;
}

int	main(void) {
	std::string		portNb;
	std::string		password;
	std::string		nick;
	int				socketFd;

	socketFd = initSocket();
	loginToServ(socketFd);
	readLoop(socketFd);
	return (0);
}

void	make_joke(std::string msg, int fd)
{
	std::string	user;
	std::string	chan;

	msg.erase(msg.begin(), msg.begin() + 1);

	user = msg.substr(0, msg.find(' '));
	msg.erase(msg.begin(),msg.begin() + msg.find(' ') + 1);
	msg.erase(msg.begin(),msg.begin() + msg.find(' ') + 1);
	chan = msg;
	chan = chan.substr(0, chan.find(' '));
	msg.erase(msg.begin(),msg.begin() + msg.find(' ') + 1);
	msg = msg.substr(0, msg.length() - 2);
	if (msg == "!joke" || msg == "!joke\n")
		send_random_joke(chan, fd);
	//  std::cout << msg << "z\n" << std::endl;
	//  std::cout << user << "t\n" << std::endl;
	//  std::cout << chan << "t\n" << std::endl;
}

int	sendMessage(const char *message, int fd) {
	int	messageSize;
	int	total;
	int	bytesleft;
	int	n;

	total = 0;
	messageSize = strlen(message);
	bytesleft = messageSize;
	while (total < messageSize) {
		n = send(fd, message + total, bytesleft, 0);
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


void	send_random_joke(std::string chan, int fd)
{
	struct timeval				time;
	int							i;
	bot							bott;
	std::string					msg;

	gettimeofday(&time, NULL);
	i = time.tv_usec % 21 + 1;

	msg = get_start_message(chan);
	msg.append("hey ");
	msg.append(chan);
	msg.append("\r\n");
	sendMessage(msg.c_str(), fd);
	msg = get_start_message(chan);
	msg.append(bott._tab[i].substr(0, bott._tab[i].find('\n') + 1));
	sendMessage(msg.c_str(), fd);
	msg = get_start_message(chan);
	msg.append(bott._tab[i].substr(bott._tab[i].find('\n') + 1, bott._tab[i].size()));
	sendMessage(msg.c_str(), fd);
}

std::string	get_start_message(std::string name)
{
	std::string					msg;

	msg = "PRIVMSG";
	msg.append(" ");
	msg.append(name);
	msg.append(" ");
	return (msg);
}
