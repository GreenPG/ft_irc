/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:06:51 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/20 16:48:17 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

static void	sendTopic(Channel *channel, User &user) {
	if (channel->get_topic().empty())
		sendMessage(RPL_NOTOPIC(user.get_nickname(), channel->get_channel_name()).c_str(), user);
	else 
		sendMessage(RPL_TOPIC(user.get_nickname(), channel->get_channel_name(), channel->get_topic()).c_str(), user);
}

static void	changeTopic(Channel *channel, std::string newTopic) {
	std::vector<User *>	userList = channel->get_chan_user_list();	

	if (newTopic[0] == ':')
		newTopic.erase(0, 1);
	if (newTopic.empty() || newTopic[0] == ':')
		channel->set_topic("");
	else
		channel->set_topic(newTopic);
	for (size_t i = 0; i < userList.size(); i++)
	{
		if (userList[i] != NULL)
			sendMessage(RPL_TOPIC(userList[i]->get_nickname(), channel->get_channel_name(), channel->get_topic()).c_str(), *userList[i]);
	}
}

static int	check_Topic_mode(Channel *channel, User &user)
{
	if (channel->is_mode_active(TOPIC) == true && channel->is_user_op(user.get_nickname()) != 0)
	{
			sendMessage(ERR_CHANOPRIVSNEEDED(user.get_nickname(), channel->get_channel_name()).c_str(), user);
			return (1);
	}
	return (0);
}

void	topic(std::string args, Server &server, User &user){
	std::string	channelName;
	size_t		idx;


	if (args.empty() || args[0] != '#') {
		sendMessage(ERR_NEEDMOREPARAMS(user.get_nickname(), "TOPIC").c_str(), user);
		return ;
	}
	idx = args.find(" ");
	if (idx == std::string::npos)
		channelName = args;
	else 
		channelName = args.substr(0, idx);
	if (search_if_exist(channelName, server.getChannelList()) == -1) {
		sendMessage(ERR_NOSUCHCHANNEL(user.get_nickname(), channelName).c_str(), user);
		return ;
	}
	idx = args.find_first_not_of(" 	", idx);
	if (check_Topic_mode(search_channel_by_name(server.getChannelList(), channelName), user) == 1)
		return ;
	if (idx == std::string::npos)
		sendTopic(search_channel_by_name(server.getChannelList(), channelName), user);
	else  {		
		changeTopic(search_channel_by_name(server.getChannelList(), channelName), args.substr(idx, args.size() - idx));
	}
}
