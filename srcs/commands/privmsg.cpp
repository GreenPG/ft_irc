/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:06:35 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/18 16:34:11 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

static void	privmsgToChannel(std::string target, std::string msg, User &currentUser, Server &server) {
	Channel	*targetChannel;

	if ((search_if_exist(target, server.getChannelList()) == 0))
		targetChannel = search_channel_by_name(server.getChannelList(), target);
	else {
		sendMessage(ERR_NOSUCHNICK(currentUser.get_nickname(), target).c_str(), currentUser);
		return ;
	}
	if (targetChannel->is_user_in_channel(currentUser.get_nickname()) == 1) {
		sendMessage(ERR_CANNOTSENDTOCHAN(currentUser.get_nickname(), target).c_str(), currentUser);
		return ;
	}
	if (msg.empty())
		sendMessage(ERR_NOTEXTTOSEND(currentUser.get_nickname()).c_str(), currentUser);
	else
		targetChannel->send_message_to_channel(RPL_PRIVMSG(currentUser.get_nickname(), target, msg).c_str(), &currentUser);
}

static void	privmsgToUser(std::string target, std::string msg, User &currentUser, std::vector<User> *userList) {
	User	*targetUser;

	if ((targetUser = search_user_by_nickname(userList, target)) == NULL)
		sendMessage(ERR_NOSUCHNICK(currentUser.get_nickname(), target).c_str(), currentUser);
	else {
		if (msg.empty()) 
			sendMessage(ERR_NOTEXTTOSEND(currentUser.get_nickname()).c_str(), currentUser);
		else 
			sendMessage(RPL_PRIVMSG(currentUser.get_nickname(), target, msg).c_str(), *targetUser );
	}
}

void	privmsg(std::string args, Server &server, User &currentUser){
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
		privmsgToChannel(target, msg, currentUser, server);
	else 
		privmsgToUser(target, msg, currentUser, server.getUserList());
}
