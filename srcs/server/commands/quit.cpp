/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:15:31 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/20 16:45:10 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

void	quit(std::string args, Server &server, User &currentUser) {

	if (args != "")
		server.sendMessageToServer(RPL_QUIT(currentUser.get_nickname(), args));
	else
		server.sendMessageToServer(RPL_QUIT(currentUser.get_nickname(), ""));
	server.remove_every_trace_of_user(&currentUser);
	FD_CLR(currentUser.get_fd_socket(), &server.getMaster());
	close(currentUser.get_fd_socket());
	server.getUserList()->erase(server.getUserList()->begin() + get_user_pos(server.getUserList(), &currentUser));
}
