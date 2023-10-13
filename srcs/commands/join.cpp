/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:29:04 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/13 09:31:03 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	join(std::string args, Server &server, user &user)
{
	int i;
	std::vector<channel>	list = server.getChannelList();
	channel new_channel;

	i = 0;

	if (search_if_exist(args, list) == 0)
		search_channel_by_name(list, args).add_user_to_channel(user);
	else
	{
		std::cout << "CHANNEL DONT EXIST BUT IS BEING CREATED" << std::endl;
		new_channel.set_channel_name(args);
		list.insert(list.end(), new_channel);
		search_channel_by_name(list, args).add_user_to_channel(user);
	}
	std::cout << "User having access to the channel " + args << std::endl;
	search_channel_by_name(list, args).print_every_user();
}

int search_if_exist(std::string args, std::vector<channel> &list)
{
	std::vector<channel>::iterator it;
	std::size_t i;

	i = 0;
	it = list.begin();
	while (i < list.size())
	{
		if (it[i].get_channel_name() == args)
			return (0);
		i++;
	}
	return (1);
}

channel &search_channel_by_name(std::vector<channel> &channel_list, std::string name)
{
	std::vector<channel>::iterator list;
	std::size_t i;

	i = 0;
	list = channel_list.begin();
	while (i < channel_list.size())
	{
		if (list[i].get_channel_name() == name)
			return (list[i]);
		i++;
	}
	return (list[i]);
}
