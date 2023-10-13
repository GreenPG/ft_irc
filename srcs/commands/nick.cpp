/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:32:19 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/13 14:11:05 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

int		checkNick(std::string nick) {
	if (nick[0] == '#' || nick[0] == ':')
		return (1);
	if (nick.find(' ') != std::string::npos)
		return (1);
	return (0);
}

void	nick(std::string args, Server &server, user &currentUser)
{
	if (args.empty()) {
		sendMessage(ERR_NONICKNAMEGIVEN(currentUser.get_nickname()).c_str(), currentUser);
		return ;
	}
	if (search_user_by_nickname(server.getUserList(), args)) {
		sendMessage(ERR_NICKNAMEINUSE(currentUser.get_nickname(), args).c_str(), currentUser);
		return ;
	}
	if (checkNick(args) == 1) {
		sendMessage(ERR_ERRONEUSNICKNAME(currentUser.get_nickname(), args).c_str(), currentUser);
		return ;
	}
	currentUser.set_nickname(args);
}
