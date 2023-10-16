/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:06:16 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/16 17:46:32 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

static void	sendModeList(std::string channelName, Server &server, User &user) {
	Channel	*channel;

	if (search_if_exist(channelName, server.getChannelList()) == 1) {
		sendMessage(ERR_NOSUCHCHANNEL(user.get_nickname(), channelName).c_str(), user);
		return ;
	}
	channel = search_channel_by_name(server.getChannelList(), channelName);
	sendMessage(RPL_CHANNELMODEIS(user.get_nickname(), channelName, channel->get_mode_list(), "").c_str(), user);
}

static void	changeMode(std::string args, std::string channelName, Server &server, User &user) {
	Channel			*channel;
	std::string		modeStr;
	std::string		modeArgsStr;
	unsigned long	idx;

	if (search_if_exist(channelName, server.getChannelList()) == 1) {
		sendMessage(ERR_NOSUCHCHANNEL(user.get_nickname(), channelName).c_str(), user);
		return ;
	}
	channel = search_channel_by_name(server.getChannelList(), channelName);
		
}

void	mode(std::string args, Server &server, User &currentUser) {
	unsigned long	idx;
	std::string		channelName;	
	
	if (args.empty() == true) {
		sendMessage(ERR_NEEDMOREPARAMS(currentUser.get_nickname(), "MODE").c_str(), currentUser);
		return ;
	}
	idx = args.find_first_of(" ", 0);
	if (idx == std::string::npos)
		sendModeList(args, server, currentUser);
	else {
		channelName = args.substr(0, idx);
		idx = args.find_first_not_of(" ", idx);
		if (idx == std::string::npos)
			sendModeList(channelName, server, currentUser);
		changeMode(args.substr(idx, args.size() - idx), channelName, server, currentUser);
	}
}
