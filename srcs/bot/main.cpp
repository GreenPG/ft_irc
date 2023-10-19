/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:14:27 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/19 16:25:02 by gpasquet         ###   ########.fr       */
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

#define LOGIN_QUERY(password, nick) ("PASS " + password + "\r\nUSER bot\r\nNICK " + nick + "\r\n")
#define	NICK_QUERY(nick) ("NICK " + nick + "\r\n")

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

int loginToServ(int socketFd) {
	std::string	password;
	std::string nick;
	std::string	response;
	int			size;
	char	buf[256];
	int nbytes;

	std::cout << "Enter server password: ";
	std::cin >> password;
	std::cout << "Enter bot nickname: ";
	std::cin >> nick;
	size = 24 + nick.size() + password.size();
	send(socketFd, LOGIN_QUERY(password, nick).c_str(), size, 0);
	while (1) {
		if ((nbytes = recv(socketFd, buf, sizeof(buf) - 1, 0)) <= 0) {
			std::cerr << "Error: receive" << std::endl;
			return (-1);
		}
		response = buf;
		if (response.substr(0, 5) == ": 001") {
			std::cout << "The bot is connected to the server" << std::endl;
			return (1);
		}
		std::cout << "Nickname already used. Enter another nickname :";
		std::cin >> nick;
		size = 24 + nick.size() + password.size();
		send(socketFd, NICK_QUERY(nick).c_str(), size, 0);
	}
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
			std::cout << buf;
			// parser(buf);
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
