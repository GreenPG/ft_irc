/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:16:49 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/18 16:41:34 by gpasquet         ###   ########.fr       */
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
#include <cstdlib>
#include "user.hpp"
#include "channel.hpp"
#include "server.hpp"
#include "replies.hpp"

class Server;
class User;
class Channel;


User		*search_user_by_socket(std::vector<User> &user_list, int fd);
User		*search_user_by_nickname(std::vector<User> *user_list, std::string name);
int			get_user_pos(std::vector<User> *user_list, User *user);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////JOIN.CPP FUNCTION///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void		join(std::string args, Server &server, User &user);
int			search_if_exist(std::string args, std::vector<Channel *> *list);
Channel		*search_channel_by_name(std::vector<Channel *> *channel_list, std::string name);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////PASS.CPP FUNCTION///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void		pass(std::string args, Server &server, User &user);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////NICK.CPP FUNCTION///////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void	nick(std::string args, Server &server, User &user);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////USER_COMMAND.CPP FUNCTION///////////////////////
////////////////////////////////////////////////////////////////////////////////


void	user_command(std::string args, Server &server, User &user);


///////////////////////////////////////////////////////////////////////////////
////////////////////////////////INVITE.CPP FUNCTION///////////////////////
////////////////////////////////////////////////////////////////////////////////

void	invite(std::string args, Server &server, User &currentUser);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////KICK.CPP FUNCTION///////////////////////
////////////////////////////////////////////////////////////////////////////////

void	kick(std::string args, Server &server, User &currentUser);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////MODE.CPP FUNCTION///////////////////////
////////////////////////////////////////////////////////////////////////////////

void	mode(std::string args, Server &server, User &currentUser);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////PRIVMSG.CPP FUNCTION///////////////////////
////////////////////////////////////////////////////////////////////////////////

void	privmsg(std::string args, Server &server, User &currentUser);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////TOPIC.CPP FUNCTION///////////////////////
////////////////////////////////////////////////////////////////////////////////

void	topic(std::string args, Server &server, User &currentUser);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////SQUIT.CPP FUNCTION///////////////////////
////////////////////////////////////////////////////////////////////////////////

void	squit(std::string args, Server &server, User &currentUser);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////UTILS.CPP FUNCTION///////////////////////
////////////////////////////////////////////////////////////////////////////////

int			is_num(std::string s);
int			check_args(int argc, char **argv);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////COMMAND POINTER TYPEDEF///////////////////////
////////////////////////////////////////////////////////////////////////////////

typedef void	(*cmdFunctions)(std::string args, Server &server, User &currentUser);


void		parser(const std::string &input, Server &server, User &currentUser);
int			sendMessage(const char *message, User &receiver);
int			get_chan_pos(std::vector<Channel *> *channel_list, Channel *chan);
#endif
