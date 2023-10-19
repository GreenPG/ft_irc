/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:14:27 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/19 15:39:34 by gpasquet         ###   ########.fr       */
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
