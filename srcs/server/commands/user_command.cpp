/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_command.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:32:19 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/19 14:25:15 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

int handleMidParams(std::string args, int *start, int *end) {
	std::string tmp;
	
	*end = args.find_first_of("	 ", *start);
	tmp = args.substr(*start, *end - *start);
	if (tmp != "0") 
		return(1);
	*start = args.find_first_not_of(" 	", *end);
	if (*start == -1)
		return (1);
	*end = args.find_first_of("	 ", *start);
	tmp = args.substr(*start, *end - *start);
	if (tmp != "*") 
		return(1);
	*start = args.find_first_not_of(" 	", *end);
	if (*start == -1)
		return (1);
	return (0);
}

void	user_command(std::string args, Server &server, User &user)
{
	std::string	userName;
	std::string realName;
	int			end;
	int			start;

	(void)server;
	if (user.checkUser() == true) {
		sendMessage(ERR_ALREADYREGISTERED(user.get_nickname()).c_str(), user); 
		return ;
	}
	end = args.find_first_of(" 	", 0);
	userName = args.substr(0, end);
	if (userName == "0") {
		sendMessage(ERR_NEEDMOREPARAMS(user.get_nickname(), "USER").c_str(), user);
		return ;
	}
	start = args.find_first_not_of(" 	", end);
	if (start == -1) {
		user.set_username(userName);
		user.setUserInit();
		if (user.check_register() == true) 
			sendMessage(RPL_WELCOME(user.get_nickname(), userName).c_str(), user);
		return ;
	}
	if (handleMidParams(args, &start, &end) == 1) {
		sendMessage(ERR_NEEDMOREPARAMS(user.get_nickname(), "USER").c_str(), user);
		return ;
	}
	realName = args.substr(start, args.size() - start);
	user.set_username(userName);
	user.setUserInit();
	if (user.check_register() == true) 
		sendMessage(RPL_WELCOME(user.get_nickname(), userName).c_str(), user);
	user.set_realname(realName);
}
