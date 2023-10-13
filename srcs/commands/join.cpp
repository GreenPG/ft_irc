/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:29:04 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/13 16:58:30 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	join(std::string args, Server &server, user &user)
{
	int 					i;
	std::vector<channel *>	*list = server.getChannelList();
	channel 				*currentChannel;

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
		currentChannel = new channel();
		currentChannel->set_channel_name(args);
		list->insert(list->end(), currentChannel);
		search_channel_by_name(list, args)->add_user_to_channel(user);
		search_channel_by_name(list, args)->add_user_as_operator(user);
	}
	currentChannel->send_message_to_channel(RPL_JOIN(user.get_nickname(), args), &server);
}

int search_if_exist(std::string args, std::vector<channel *> *list)
{
	std::vector<channel *>::iterator it;
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

channel *search_channel_by_name(std::vector<channel *> *channel_list, std::string name)
{
	std::size_t i;
	std::vector<channel *>::iterator it;

	i = 0;
	it = channel_list->begin();
	while (i < channel_list->size())
	{
		if (it[i]->get_channel_name() == name)
			return (it[i]);
		i++;
	}
	return (it[i]);
	}
