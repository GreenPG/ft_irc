/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:16:49 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/10 17:53:14 by gpasquet         ###   ########.fr       */
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

class user;


void	parser(const std::string input, user &currentUser);
int		sendMessage(const char *message, user &receiver);

#endif
