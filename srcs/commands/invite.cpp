/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:00:54 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/18 17:11:11 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	invite(std::string args, Server &server, User &currentUser) {
	std::string		nick;
	std::string		channelName;
	unsigned long	idx;
	Channel			*channel;

	idx = args.find(" ", 0);
	if (args.empty() || idx == std::string::npos) {
		sendMessage(ERR_NEEDMOREPARAMS(currentUser.get_nickname(), "INVITE").c_str(), currentUser);
		return;
	}
	nick = args.substr(0, idx);
	idx = args.find_first_not_of(" ", idx);
	if (idx == std::string::npos) {
		sendMessage(ERR_NEEDMOREPARAMS(currentUser.get_nickname(), "INVITE").c_str(), currentUser);
		return;
	}
	channelName = args.substr(idx, args.size() - idx);
	if (search_if_exist(channelName, server.getChannelList()) == 1) {
		sendMessage(ERR_NOSUCHCHANNEL(currentUser.get_nickname(), channelName).c_str(), currentUser);
		return;
	}
	if (search_user_by_nickname(server.getUserList(), nick) == NULL) {
		sendMessage(ERR_NOSUCHNICK(currentUser.get_nickname(), nick).c_str(), currentUser);
		return ;
	}
	channel = search_channel_by_name(server.getChannelList(), channelName);
	if (channel->is_user_in_channel(currentUser.get_nickname())) {
			sendMessage(ERR_NOTONCHANNEL(currentUser.get_nickname(), channelName).c_str(), currentUser);
			return ;
	}
	if (channel->is_user_in_channel(nick) == 0) {
		sendMessage(ERR_USERONCHANNEL(currentUser.get_nickname(), nick, channelName).c_str(), currentUser);
		return ;
	}
	if (channel->is_mode_active(INVITE) == true) {
		if (channel->is_user_op(currentUser.get_nickname())) {
			sendMessage(ERR_CHANOPRIVSNEEDED(currentUser.get_nickname(), channelName).c_str(), currentUser);
			return ;
		}
		else 
			channel->add_user_as_invited(*search_user_by_nickname(server.getUserList(), nick));
	}
	sendMessage(RPL_INVITING(currentUser.get_nickname(), nick, channelName).c_str(), currentUser);
	sendMessage(INVITE(currentUser.get_nickname(), nick, channelName).c_str(), *search_user_by_nickname(server.getUserList(), nick));
}
