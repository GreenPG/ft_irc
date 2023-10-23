/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skill.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:15:31 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/23 11:20:09 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

void	skill(std::string args, Server &server, User &currentUser) {
	std::vector<User *>		u_list = *server.getUserList();

	for(size_t i = 0; i< server.getUserList()->size(); i++)
	{
		sendMessage(":command to close the server\r\n", *u_list[i]);
	}
	server.setQuit();
	(void)args;
	(void)currentUser;
}
