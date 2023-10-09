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

void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char **argv) {
	struct addrinfo	 hints;
	struct addrinfo	 *servinfo;
	struct addrinfo *p;
	int rv;
	int listener;
	// int newfd;

	(void)argc;
	memset(&hints, 0, sizeof hints);
	hints.ai_family	= AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	rv = getaddrinfo(NULL, argv[1], &hints, &servinfo);

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
		perror("listen:");
		exit(1);
	}

	fd_set	master;
	fd_set	readfds;

	FD_ZERO(&master);
	FD_ZERO(&readfds);
	FD_SET(listener, &master);

	int fd_max = listener;
	int new_fd;
	int nbytes;
	socklen_t	addrlen;
	struct sockaddr_storage remoteaddr;
	char remoteIP[INET6_ADDRSTRLEN];
	char	buf[256];

	while(1) {
		readfds = master;
		if (select(fd_max + 1, &readfds, NULL, NULL, NULL) == -1) {
			perror("Select:");
			exit(1);
		}

		for (int i = 0; i <= fd_max; i++) {
			if (FD_ISSET(i, &readfds)) {
				if (i == listener) {
					addrlen = sizeof(remoteaddr);
					new_fd = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen);
					if (new_fd == -1) 
						perror("accept:");
					else {
						FD_SET(new_fd, &master);
						if (new_fd > fd_max)
							fd_max = new_fd;
					}
					printf("selectserver: new connection from %s on socket %d\n", inet_ntop(remoteaddr.ss_family,  get_in_addr((struct sockaddr*)&remoteaddr), remoteIP, INET6_ADDRSTRLEN), new_fd);
				}

				else {
					if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0) {
						if (nbytes == 0)
							printf("selectserver: socket %d hung up\n", i);
						else 
							perror("recv:");
						close(i);
						FD_CLR(i, &master);
					}
					else {
						for (int j = 0; j <= fd_max; j++) {
							if (FD_ISSET(j, &master)) {
								if (j != listener && j != i) {
									printf("j = %i\n", j);
									if (send(j, buf, nbytes, 0) == -1)
										perror("send");
								}
							}
						}
					}
				}
			}
		}
	}
	close(listener);
	return (1);
}
