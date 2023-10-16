/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squit.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:15:31 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/16 17:06:40 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	squit(std::string args, Server &server, User &currentUser) {

	size_t								i;
	std::vector<User>::iterator			u_list;
	std::vector<Channel *>	channelList = *server.getChannelList();

	i = 0;
	u_list = server.getUserList()->begin();

	while (i < server.getUserList()->size())
	{
		sendMessage(":command to close the server\r\n", u_list[i]);
		i++;
	}
    while (channelList.size() != 0)
	{
        delete channelList.back();
        channelList.pop_back();
    }
	server.setQuit();
	(void)args;
	(void)server;
	(void)currentUser;
}

