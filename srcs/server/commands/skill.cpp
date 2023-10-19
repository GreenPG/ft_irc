/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skill.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:15:31 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/19 14:25:02 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

void	skill(std::string args, Server &server, User &currentUser) {

	size_t								i;
	std::vector<User>::iterator			u_list;
	std::vector<Channel *>	channelList = *server.getChannelList();

	i = 0;
	u_list = server.getUserList()->begin();

	while (i < server.getUserList()->size())
	{
		sendMessage(":command to close the server\r\n", u_list[i]);
		close(u_list[i].get_fd_socket());
		i++;
	}
	while (channelList.size() != 0)
	{
		delete channelList.back();
		channelList.pop_back();
	}
	server.setQuit();
	(void)args;
	(void)currentUser;
}

