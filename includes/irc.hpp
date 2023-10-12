/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:16:49 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/12 16:09:39 by tlarraze         ###   ########.fr       */
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
#include "server.hpp"
#include "replies.hpp"

class Server;
class user;
class channel;



user		*search_user_by_socket(std::vector<user> &user_list, int fd);
user		*search_user_by_nickname(std::vector<user> &user_list, std::string name);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////JOIN.CPP FUNCTION///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void		join(std::string args, Server &server, user &user);
int			search_if_exist(std::string args, std::vector<channel> &list);
channel		&search_channel_by_name(std::vector<channel> &channel_list, std::string name);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////PASS.CPP FUNCTION///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void		pass(std::string args, Server &server, user &user);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////NICK.CPP FUNCTION///////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void	nick(std::string args, Server &server, user &user);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////USER_COMMAND.CPP FUNCTION///////////////////////
////////////////////////////////////////////////////////////////////////////////


void	user_command(std::string args, Server &server, user &user);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////CAP.CPP FUNCTION///////////////////////
////////////////////////////////////////////////////////////////////////////////


void	cap(std::string args, Server &server, user &currentUser);

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////INVITE.CPP FUNCTION///////////////////////
////////////////////////////////////////////////////////////////////////////////

void	invite(std::string args, Server &server, user &currentUser);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////KICK.CPP FUNCTION///////////////////////
////////////////////////////////////////////////////////////////////////////////

void	kick(std::string args, Server &server, user &currentUser);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////MODE.CPP FUNCTION///////////////////////
////////////////////////////////////////////////////////////////////////////////

void	mode(std::string args, Server &server, user &currentUser);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////PRIVMSG.CPP FUNCTION///////////////////////
////////////////////////////////////////////////////////////////////////////////

void	privmsg(std::string args, Server &server, user &currentUser);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////TOPIC.CPP FUNCTION///////////////////////
////////////////////////////////////////////////////////////////////////////////

void	topic(std::string args, Server &server, user &currentUser);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////COMMAND POINTER TYPEDEF///////////////////////
////////////////////////////////////////////////////////////////////////////////

typedef void	(*cmdFunctions)(std::string args, Server &server, user &currentUser);


void		parser(const std::string &input, Server &server, user &currentUser);
int			sendMessage(const char *message, user &receiver);

#endif
