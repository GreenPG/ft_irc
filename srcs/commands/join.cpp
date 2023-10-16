/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:29:04 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/16 14:57:46 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

static std::string	createUserList(Channel *channel) {
	std::string			list;
	std::vector<User>	userList = channel->get_chan_user_list();

	for (size_t i = 0; i < userList.size(); i++) {
		if (channel->is_user_op(userList[i].get_nickname()) == 0)
			list.append("@");
		list.append(userList[i].get_nickname());
		if (i < userList.size() - 1)
			list.append(" ");
	}
	return (list);
}

void	join(std::string args, Server &server, User &user)
{
	int 					i;
	std::vector<Channel *>	*list = server.getChannelList();
	Channel 				*currentChannel;
	std::string				prefix;
	std::string				userList;

	i = 0;

	if (args == "" || args[0] != '#')
	{
		sendMessage(ERR_BADCHANMASK(user.get_nickname(), args).c_str(), user);
		return ;
	}
	if (search_if_exist(args, list) == 0) {
		currentChannel = search_channel_by_name(list, args);
		currentChannel->add_user_to_channel(user);
	}
	else
	{
		currentChannel = new Channel();
		currentChannel->set_channel_name(args);
		list->insert(list->end(), currentChannel);
		search_channel_by_name(list, args)->add_user_to_channel(user);
		search_channel_by_name(list, args)->add_user_as_operator(user);
	}
	currentChannel->send_message_to_channel(RPL_JOIN(user.get_nickname(), args), &server);
	if (currentChannel->get_topic().empty() == false)
		sendMessage(RPL_TOPIC(user.get_nickname(), currentChannel->get_channel_name(), currentChannel->get_topic()).c_str(), user);
	userList = createUserList(currentChannel);
	sendMessage(RPL_NAMREPLY(user.get_nickname(), currentChannel->get_channel_name(), userList).c_str(), user);
	sendMessage(RPL_ENDOFNAMES(user.get_nickname(), currentChannel->get_channel_name()).c_str(), user);
}

int search_if_exist(std::string args, std::vector<Channel *> *list)
{
	std::vector<Channel *>::iterator it;
	std::size_t i;

	i = 0;
	it = list->begin();
	while (i < list->size())
	{
		if (it[i]->get_channel_name() == args)
			return (0);
		i++;
	}
	return (1);
}

Channel *search_channel_by_name(std::vector<Channel *> *channel_list, std::string name)
{
	std::size_t i;
	std::vector<Channel *> channelList = *channel_list;
	i = 0;
	while (i < channelList.size())
	{
		if (channelList[i]->get_channel_name() == name)
			return (channelList[i]);
		i++;
	}
	return (NULL);
}
