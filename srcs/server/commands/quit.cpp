/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:15:31 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/23 13:59:02 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

void	quit(std::string args, Server &server, User &currentUser) {

	User	*u;

	u = &currentUser;
	if (args != "")
		server.sendMessageToServer(RPL_QUIT(currentUser.get_nickname(), args));
	else
		server.sendMessageToServer(RPL_QUIT(currentUser.get_nickname(), ""));
	server.remove_every_trace_of_user(&currentUser);
	FD_CLR(currentUser.get_fd_socket(), &server.getMaster());
	close(currentUser.get_fd_socket());
	delete u;
	server.getUserList()->erase(server.getUserList()->begin() + get_user_pos(*server.getUserList(), &currentUser));
}
