/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:06:35 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/13 10:07:05 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

static void	privmsgToChannel() {
}

static void	privmsgToUser(std::string target, std::string msg, user &currentUser, std::vector<user> userList) {
	user	*targetUser;

	if ((targetUser = search_user_by_nickname(userList, target)) == NULL)
		sendMessage(ERR_NOSUCHNICK(currentUser.get_nickname(), target).c_str(), currentUser);
	else {
		if (msg.empty()) 
			sendMessage(ERR_NOTEXTTOSEND(currentUser.get_nickname()).c_str(), currentUser);
		else 
			sendMessage(RPL_PRIVMSG(currentUser.get_nickname(), currentUser.get_username(), target, msg).c_str(), *targetUser );
	}
}

void	privmsg(std::string args, Server &server, user &currentUser){
	int start;
	int	end;
	std::string	target;
	std::string	msg;

	start = args.find_first_not_of(" 	");
	end = args.find_first_of(" 	", start);
	if (start == -1 || end == -1) {
		sendMessage(ERR_NORECIPIENT(currentUser.get_nickname(), "PRIVMSG").c_str(), currentUser);
		return ;
	}
	target = args.substr(start, end - start);
	if (target.empty()) {
		sendMessage(ERR_NORECIPIENT(currentUser.get_nickname(), "PRIVMSG").c_str(), currentUser);
		return ;
	}
	start = args.find_first_not_of(" 	", end);
	msg = args.substr(start, args.size() - start);
	if (target[0] == '#')
		privmsgToChannel();
	else 
		privmsgToUser(target, msg, currentUser, server.getUserList());
}
