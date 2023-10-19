/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:14:27 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/19 16:25:43 by tlarraze         ###   ########.fr       */
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

#include "joke_database.hpp"
#include "bot.hpp"
#include <sys/time.h>
#include <vector>

static void	make_joke(std::string msg, int fd);
static void	send_random_joke(std::string user, std::string chan, int fd);
static std::string	get_start_message(std::string name);

int	initSocket() {
	struct addrinfo	hints;
	struct addrinfo	*servinfo;
	struct addrinfo	*p;
	int				socketFd;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(NULL, "6697", &hints, &servinfo) != 0) {
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

int loginToServ(int socketFd) {
	send(socketFd, "PASS 1\r\nNICK bot\r\nUSER bot\r\n", 29, 0);
	return (1);
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
		if ((nbytes = recv(socketFd, buf, sizeof(buf) - 1, 0) <= 0))
			std::cerr << "Error: receive" << std::endl;
		else {
			make_joke(buf, socketFd);
		}
	}
}

int	main(void) {
	std::string		portNb;
	std::string		password;
	std::string		nick;
	int				socketFd;

	socketFd = initSocket();
	if (loginToServ(socketFd))
		readLoop(socketFd);
	return (0);
}

// int	main(int argc, char **argv) {
// 	if (argc < 1)
// 		return (0);
// 	make_joke(argv[1]);	
// }
//:DUDE PRIVMSG bot !joke					//priv
//:DUDE PRIVMSG #CHAN !joke					//chan
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
	if (msg == "!joke")
		send_random_joke(user, chan, fd);
	// std::cout << msg << "\n" << std::endl;
	// std::cout << user << "\n" << std::endl;
	// std::cout << chan << "\n" << std::endl;
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


void	send_random_joke(std::string user, std::string chan, int fd)
{
	struct timeval				time;
	int							i;
	bot							bott;
	std::string					msg;

	gettimeofday(&time, NULL);
	i = time.tv_usec % 21 + 1;

	if (chan[0] != '#')
	{
		msg = get_start_message(user);
		msg.append("hey ");
		msg.append(user);
		msg.append("\n");
		sendMessage(msg.c_str(), fd);
		msg = get_start_message(user);
		msg.append(bott._tab[i].substr(0, bott._tab[i].find('\n') + 1));
		sendMessage(msg.c_str(), fd);
		msg = get_start_message(user);
		msg.append(bott._tab[i].substr(bott._tab[i].find('\n') + 1, bott._tab[i].size()));
		sendMessage(msg.c_str(), fd);
		sendMessage("dwqdwqdwqdwq", fd);
	}
	(void)user;
	(void)chan;
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