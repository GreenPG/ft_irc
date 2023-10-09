#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>	
#include <iostream>
#include <cstdio>

struct addrinfo initHints(void) {
	struct addrinfo	 hints;

	memset(&hints, 0, sizeof hints);
	hints.ai_family	= AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	return (hints);	
}

int	initServer(const char *portNb) {
	int	listener;
	int rv;
	struct addrinfo	 hints;
	struct addrinfo	 *servinfo;
	struct addrinfo *p;

	hints = initHints();
	rv = getaddrinfo(NULL, portNb, &hints, &servinfo); 
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("socket:");
			continue;
		}
		if (bind(listener, p->ai_addr, p->ai_addrlen) == -1) {
			close(listener);
			perror("bind:");
			continue;
		}
		break;
	}
	freeaddrinfo(servinfo);
	if (p == NULL) {
		std::cout << ("bind error");
		exit(1);
	}

	if (listen(listener, 10) == -1) {
		std::perror("listen:");
		exit(1);
	}
	return(listener);
}

void	initFdsets(fd_set &master, fd_set &readFds, int &listener) {
	FD_ZERO(&master);
	FD_ZERO(&readFds);
	FD_SET(listener, &master);
}

void	newConnection(fd_set &master, int &listener, int &fdMax) {
	struct sockaddr_storage remoteAddr;
	socklen_t	addrLen;
	int newFd;
	
	addrLen = sizeof(remoteAddr);
	newFd = accept(listener, (struct sockaddr *)&remoteAddr, &addrLen);
	if (newFd == -1) 
		perror("accept:");
	else {
		std::cout << "newFd: " << newFd << std::endl;
		FD_SET(newFd, &master);
		if (newFd > fdMax)
			fdMax = newFd;
	}
}

void	receiveError(const int &nbytes, int &socketFd, fd_set &master) {
	if (nbytes == 0)
		printf("selectserver: socket %d hung up\n", socketFd);
	else 
		perror("recv:");
	close(socketFd);
	FD_CLR(socketFd, &master);
}

void	receiveData(fd_set &master, int &listener, int &fdMax, int &socketFd) {
	int 	nbytes;
	char	buf[256];


	if (socketFd == listener) {
		newConnection(master, listener, fdMax);
	}
	else {
		if ((nbytes = recv(socketFd, buf, sizeof(buf), 0)) <= 0)
			receiveError(nbytes, socketFd, master);
		else {
			for (int j = 0; j <= fdMax; j++) {
				if (FD_ISSET(j, &master)) {
					if (j != listener && j != socketFd) {
						if (send(j, buf, nbytes, 0) == -1)
							perror("send");
					}
				}
			}
		}
	}
}

void	readLoop(fd_set &master, fd_set &readFds, int &listener, int &fdMax) {
	for (int i = 0; i <= fdMax; i++) {
		if (FD_ISSET(i, &readFds))
			receiveData(master, listener, fdMax, i);
	}
}

int main(int argc, char **argv) {
	int 	listener;
	fd_set	master;
	fd_set	readFds;
	int 	fdMax;

	if (argc != 2) {
		std::cout << "Port number expected" << std::endl;
		exit(1);
	}
	listener = initServer(argv[1]);
	initFdsets(master, readFds, listener);
	fdMax = listener;
	while(1) {
		readFds = master;
		if (select(fdMax + 1, &readFds, NULL, NULL, NULL) == -1) {
			perror("Select:");
			exit(1);
		}
		readLoop(master, readFds, listener, fdMax);
	}
	FD_ZERO(&master);
	FD_ZERO(&readFds);
	close(listener);
	return (1);
}
