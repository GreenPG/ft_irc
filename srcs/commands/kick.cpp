/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:03:43 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/13 15:54:19 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	kick(std::string args, Server &server, user &user) {
	(void)server;
	(void)user;
	std::string		channel_arg;
	std::string		user_arg;
	std::string		msg_arg;
	
	channel_arg = args;
	user_arg = args;
	channel_arg.resize(channel_arg.find(' ', 0));
	user_arg.erase(0, user_arg.find(' ', 0) + 1);
	msg_arg = user_arg;
	if (user_arg.find(' ', 0) != std::string::npos)
	{
		msg_arg.erase(0, msg_arg.find(' ', 0) + 1);
		user_arg.resize(user_arg.find(' ', 0));
		//msg_arg.resize(msg_arg.find(' ', 0) + 1);
	}
	else
		msg_arg = "";
		
	std::cout << "FULL ARGS " << args << "\n" << std::endl;
	std::cout << "CHANNEL ARGS " << channel_arg << "\n" << std::endl;
	std::cout << "USER ARGS " << user_arg << "\n" << std::endl;
	std::cout << "MSG ARGS " << msg_arg << "\n" << std::endl;
}
