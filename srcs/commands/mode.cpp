/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:06:16 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/17 15:36:49 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

static void	sendModeList(std::string channelName, Server &server, User &user) {
	Channel		*channel;
	std::string channelMode;

	if (search_if_exist(channelName, server.getChannelList()) == 1) {
		sendMessage(ERR_NOSUCHCHANNEL(user.get_nickname(), channelName).c_str(), user);
		return ;
	}
	channel = search_channel_by_name(server.getChannelList(), channelName);
	channelMode = channel->get_mode_list();
	if (channelMode.empty() == false)
		channelMode.insert(0, "");
	sendMessage(RPL_CHANNELMODEIS(user.get_nickname(), channelName, channelMode, "").c_str(), user);
}

static int	addOp(std::string nick, Server &server, Channel *channel, User &user) {
	if (channel->is_user_in_channel(nick)) { 
		sendMessage(ERR_USERNOTINCHANNEL(user.get_nickname(), nick, channel->get_channel_name()).c_str(), user);
		return 0;
	}
	if (channel->is_user_op(nick))
		channel->add_user_as_operator(*search_user_by_nickname(server.getUserList(), nick));
	return (1);
}

static int	addKey(std::string key, Channel *channel, User &user) {
	if (key.empty()) {
		sendMessage(ERR_INVALIDMODEPARAM(user.get_nickname(), channel->get_channel_name(), "k", key, "Empty key").c_str(), user);
		return (0);
	}
	if (key.find(" ", 0) != std::string::npos) {
		sendMessage(ERR_INVALIDMODEPARAM(user.get_nickname(), channel->get_channel_name(), "k", key, "Space(s) in key").c_str(), user);
		return (0);
	}
	channel->set_password(key);
	return (1);
}

static int addLimit(std::string limit, Channel *channel, User &user) {
	if (limit.empty()) {
		sendMessage(ERR_INVALIDMODEPARAM(user.get_nickname(), channel->get_channel_name(), "l", limit, "No limit given").c_str(), user);
		return (0);

	}
	for (size_t i = 0; i < limit.size(); i++) {
		if (isdigit(limit[i]) == 0) {
			sendMessage(ERR_INVALIDMODEPARAM(user.get_nickname(), channel->get_channel_name(), "l", limit, "Limit is not a number").c_str(), user);
			return (0);
		}
	}
	channel->set_limit(atoi(limit.c_str()));
	return (1);
}


static void	getNextArg(unsigned long *nextArgsIdx, unsigned long *commaIdx, std::string &modeArgs, std::string &currentArg) {
	if (nextArgsIdx && *nextArgsIdx == std::string::npos)
		currentArg = "";
	else {
		*commaIdx = modeArgs.find(",", *nextArgsIdx);
		currentArg = modeArgs.substr(*nextArgsIdx, *commaIdx - *nextArgsIdx);
		*nextArgsIdx = modeArgs.find_first_not_of(",", *commaIdx);
	}
}

static void	addMode(std::string modeStr, std::string modeArgs, Server &server, Channel *channel, User &user) {
	std::string		modeRpl = "+";
	std::string		argsRpl;
	std::string		unknownFlags;
	std::string		currentArg;
	unsigned long	commaIdx = 0;
	unsigned long	nextArgsIdx = std::string::npos;
 
	if (modeArgs.empty() == false) {
		commaIdx = modeArgs.find(",", 0);
		currentArg = modeArgs.substr(0, commaIdx);
		nextArgsIdx = modeArgs.find_first_not_of(",", commaIdx);
	}
	else 
		currentArg = "";
	for (size_t i = 0; i < modeStr.size(); i++) {

		if (modeStr[i] == 'i') {
			channel->add_mode(INVITE);
			modeRpl.append("i");
		}	
		else if (modeStr[i] == 't') {
			channel->add_mode(TOPIC);
			modeRpl.append("t");
		}	
		else if (modeStr[i] == 'k') {
			if (addKey(currentArg, channel, user)) {
				channel->add_mode(KEY);
				modeRpl.append("k");
				if (argsRpl.empty() == false)
					argsRpl.append(" ");
				argsRpl.append(currentArg);
			}
			getNextArg(&nextArgsIdx, &commaIdx, modeArgs, currentArg);
		}	
		else if (modeStr[i] == 'l') {
			if (addLimit(currentArg, channel, user)) {
				channel->add_mode(LIMIT);
				modeRpl.append("l");
				if (argsRpl.empty() == false)
					argsRpl.append(" ");
				argsRpl.append(currentArg);
			}
			getNextArg(&nextArgsIdx, &commaIdx, modeArgs, currentArg);
		}
		else if (modeStr[i] == 'o') {
			if (addOp(currentArg, server, channel ,user)) { 
				modeRpl.append("o");
				if (argsRpl.empty() == false)
					argsRpl.append(" ");
				argsRpl.append(currentArg);
			}
			getNextArg(&nextArgsIdx, &commaIdx, modeArgs, currentArg);
		}	
		else
			unknownFlags.append(modeStr.substr(i, 1));
	}
	channel->send_message_to_channel(MODE(user.get_nickname(), channel->get_channel_name(), modeRpl, argsRpl).c_str());
	if (unknownFlags.empty() == false)
		sendMessage(ERR_UMODEUNKNOWNFLAG(user.get_nickname(), unknownFlags).c_str(), user);
}
/*
   static void	delMode(std::string modeStr, std::string modeArgs, Channel *channel, User &user) {

   }*/

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
	if (channel->is_user_in_channel(user.get_nickname()) == 1) {
		sendMessage(ERR_NOTONCHANNEL(user.get_nickname(), channelName).c_str(), user);
		return ;
	}
	if (channel->is_user_op(user.get_nickname()) == 1) {
		sendMessage(ERR_CHANOPRIVSNEEDED(user.get_nickname(), channelName).c_str(), user);
		return ;
	}
	idx = args.find(" ", 0);
	if (idx == std::string::npos) {
		modeStr = args;
		modeArgsStr = "";
	}
	else {
		modeStr = args.substr(0, idx);
		idx = args.find_first_not_of(" ", idx);
		if (idx == std::string::npos)
			modeArgsStr = "";
		else 
			modeArgsStr = args.substr(idx, args.size() - idx);
	}
	if (modeStr[0] == '+')
		addMode(modeStr.substr(1), modeArgsStr, server, channel, user);
	// else if (modeStr[0] == '-'){
	// delMode(modeStr.substr(1), modeArgsStr, channel, user);
	else 
		sendMessage(ERR_NEEDMOREPARAMS(user.get_nickname(), "MODE").c_str(), user);
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
		else 
			changeMode(args.substr(idx, args.size() - idx), channelName, server, currentUser);
	}
}
