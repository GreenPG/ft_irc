/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:16:49 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/11 16:38:55 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

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
#include <vector>
#include "user.hpp"
#include "channel.hpp"

user		*search_user_by_socket(std::vector<user> &user_list, int fd);
user		*search_user_by_nickname(std::vector<user> &user_list, std::string name);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////JOIN.CPP FUNCTION///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int			join(std::string args, std::vector<channel> &list, user &user);
int			search_if_exist(std::string args, std::vector<channel> &list);
channel		&search_channel_by_name(std::vector<channel> &channel_list, std::string name);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////PASS.CPP FUNCTION///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void		pass(std::string args, user &user);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////NICK.CPP FUNCTION///////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void		nick(std::string args, user &user);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////USER_COMMAND.CPP FUNCTION///////////////////////
////////////////////////////////////////////////////////////////////////////////


void		user_command(std::string args, user &user);


void		receiveData(fd_set &master, int &listener, int &fdMax, int &socketFd, std::vector<user> &user_list, std::vector<channel> &channel_list);
void		parser(const std::string &input, std::vector<channel> &channel_list, user &user);
int			sendMessage(const char *message, user &receiver);
void		readLoop(fd_set &master, fd_set &readFds, int &listener, int &fdMax, std::vector<user> &user_list, std::vector<channel> &channel_list);

#endif
