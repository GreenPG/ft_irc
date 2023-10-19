/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:32:19 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/19 14:24:26 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

int		checkNick(std::string nick) {
	if (nick[0] == '#' || nick[0] == ':')
		return (1);
	if (nick.find(' ') != std::string::npos)
		return (1);
	return (0);
}

void	initNick(std::string nick, User &currentUser) {
	currentUser.set_nickname(nick);
	currentUser.setNickInit();
	if (currentUser.check_register() == true)
		sendMessage(RPL_WELCOME(currentUser.get_nickname(), currentUser.get_username()).c_str(), currentUser);
}

void	changeNick(std::string newNick, Server &server, User &currentUser) {
	std::string	oldNick;

	oldNick = currentUser.get_nickname();
	currentUser.set_nickname(newNick);
	currentUser.setNickInit();
	server.sendMessageToServer(RPL_NICK(oldNick, currentUser.get_username(), newNick));
}

void	nick(std::string args, Server &server, User &currentUser)
{
	std::string	oldNick;

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
	if (currentUser.checkNick() == false)
		initNick(args, currentUser);
	else
		changeNick(args, server, currentUser);
}
