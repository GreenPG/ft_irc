/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:16:22 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/10 15:58:37 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

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

void	receiveData(fd_set &master, int &listener, int &fdMax, int &socketFd, std::vector<user> *user_list) {
	int 				nbytes;
	char				buf[256];
	user				new_user;

	if (socketFd == listener) {
		newConnection(master, listener, fdMax);
		new_user.set_fd_socket(fdMax);
		user_list->insert(user_list->end(), new_user);
		std::cout << "Asking password to " << new_user.get_fd_socket() << std::endl;
		send(fdMax, "Send password bro\n", 18, 0);


	}
	else {
		if ((nbytes = recv(socketFd, buf, sizeof(buf), 0)) <= 0)
			receiveError(nbytes, socketFd, master);
		else {
			for (int j = 0; j <= fdMax; j++) {
				if (FD_ISSET(j, &master)) {
					if (search_user_by_socket(user_list, j)->get_fd_socket() == socketFd && search_user_by_socket(user_list, j)->check_register() != 0)
					{
							search_user_by_socket(user_list, j)->register_user(buf);
					}
					else if (j != listener && j != socketFd && search_user_by_socket(user_list, j)->check_register() == 0) {
						if (send(j, buf, nbytes, 0) == -1 && search_user_by_socket(user_list, j)->check_register() == 0)
							perror("send");
					}
				}
			}
		}
	}
}

void	readLoop(fd_set &master, fd_set &readFds, int &listener, int &fdMax, std::vector<user> *user_list) {
	for (int i = 0; i <= fdMax; i++) {
		if (FD_ISSET(i, &readFds))
			receiveData(master, listener, fdMax, i, user_list);
	}
}



int main(int argc, char **argv) {
	int 	listener;
	fd_set	master;
	fd_set	readFds;
	int 	fdMax;
	std::vector<user>	user_list;

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
		readLoop(master, readFds, listener, fdMax, &user_list);
	}
	FD_ZERO(&master);
	FD_ZERO(&readFds);
	close(listener);
	return (1);
}
