/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:49:17 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/18 11:48:33 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.hpp"
#include <asm-generic/socket.h>
#include <sys/socket.h>

Server::Server(): _listener(-1), _fdMax(-1) {
	FD_ZERO(&this->_master);
	FD_ZERO(&this->_readFds);
	_listener = -1;
	_password = "1";
	_quit = 0;
}

Server::~Server() {
	if (_listener != -1)
		close(this->_listener);
	FD_ZERO(&this->_master);
	FD_ZERO(&this->_readFds);
}	

int						&Server::getListener() {
	return (this->_listener);
}

int						&Server::getFdMax() {
	return (this->_fdMax);
}

fd_set					&Server::getMaster() {
	return (this->_master);
}

fd_set					&Server::getReadFds() {
	return (this->_readFds);
}

std::vector<User>		*Server::getUserList() {
	return (&_userList);
}

std::vector<Channel *>	*Server::getChannelList() {
	return (&_channelList);
}

void					Server::initServer(const char *portNb) {
	struct addrinfo	 hints;
	struct addrinfo	 *servinfo;
	struct addrinfo *p;
	int	yes = 1;

	hints = initHints();
	getaddrinfo(NULL, portNb, &hints, &servinfo); 
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((this->_listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("socket:");
			continue;
		}
		setsockopt(this->_listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		if (bind(this->_listener, p->ai_addr, p->ai_addrlen) == -1) {
			close(this->_listener);
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

	if (listen(this->_listener, 10) == -1) {
		std::perror("listen:");
		exit(1);
	}
	FD_SET(this->_listener, &this->_master);
	this->_fdMax = this->_listener;
}

void	Server::listenLoop() {
	while(getQuit() == 0) {
		this->_readFds = this->_master;
		if (select(this->_fdMax + 1, &this->_readFds, NULL, NULL, NULL) == -1) {
			perror("Select:");
			exit(1);
		}
		this->readLoop();
	}
}

User	&Server::identifyUser(const int userFd) {

	std::vector<User>::iterator		list;
	std::size_t						i;

	i = 0;
	list = _userList.begin();
	while (i < _userList.size())
	{
		if (list[i].get_fd_socket() == userFd)
			return (list[i]);
		i++;
	}
	return (list[i]);
}

struct addrinfo Server::initHints(void) {

	struct addrinfo	 hints;

	memset(&hints, 0, sizeof hints);
	hints.ai_family	= AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = IPPROTO_TCP;
	return (hints);	
}

int	Server::newConnection() {
	struct sockaddr_storage remoteAddr;
	socklen_t	addrLen;
	int newFd;
	
	addrLen = sizeof(remoteAddr);
	newFd = accept(this->_listener, (struct sockaddr *)&remoteAddr, &addrLen);
	if (newFd == -1) 
		perror("accept:");
	else if (this->_userNb == 1000)
		perror("Server full:");
	else {
		std::cout << "newFd: " << newFd << std::endl;
		FD_SET(newFd, &this->_master);
		incUser();
		if (newFd > this->_fdMax)
			this->_fdMax = newFd;
	}
	return (newFd);
}

void	Server::receiveError(const int &nbytes, int &socketFd) {


	if (nbytes == 0)
		printf("selectserver: socket %d hung up\n", socketFd);
	else 
		perror("recv:");
	close(socketFd);
	FD_CLR(socketFd, &this->_master);
	if (get_user_pos(&_userList, search_user_by_socket(_userList, socketFd)) != -1) {
		_userList.erase(_userList.begin() + get_user_pos(&_userList, search_user_by_socket(_userList, socketFd)));
		decUser();
	}

	///////////need to also remove him from every channel he is
	///////////and kick + deop him of every
}

int		get_user_pos(std::vector<User> *user_list, User *user)
{
	size_t					i;
	std::vector<User>::iterator		list;

	list = user_list->begin();

	i = 0;
	while (list != user_list->end())
	{
		if (user->get_nickname() == list[0].get_nickname())
			return (i);
		list++;
		i++;
	}
	if (user->get_nickname() == list[0].get_nickname())
		return (i);
	std::cout << "DIDNT QWORDK\n" << std::endl;
	return (-1);
}

void	Server::receiveData(int &socketFd) {
	int 				nbytes;
	int 				newUserFd;
	char				buf[256];
	User				new_user;
	User				*currentUser;

	if (socketFd == this->_listener) {
		newUserFd = newConnection();
		new_user.set_fd_socket(newUserFd);
		this->_userList.insert(this->_userList.end(), new_user);
		std::cout << "Asking password to " << new_user.get_fd_socket() << std::endl;
		send(this->_fdMax, "Send password bro\n", 18, 0);
	}
	else {
		currentUser = &identifyUser(socketFd);
		if ((nbytes = recv(socketFd, buf, sizeof(buf), 0)) <= 0)
			receiveError(nbytes, socketFd);
		else {
			parser(buf, *this, *currentUser);
			std::cout << buf << std::endl;
			}
		memset(&buf, 0, 256);
	}
}

void	Server::readLoop() {
	for (int i = 0; i <= this->_fdMax; i++) {
		if (FD_ISSET(i, &this->_readFds))
			receiveData(i);
	}
}

std::string	&Server::getPassword()
{
	return (_password);
}

void	Server::setPassword(std::string Pass)
{
	_password = Pass;
}

void	Server::setQuit()
{
	_quit = 1;
}

int	Server::getQuit()
{
	return (_quit);
}

void					Server::incUser() {
	this->_userNb++;
}

void					Server::decUser() {
	this->_userNb--;
}
