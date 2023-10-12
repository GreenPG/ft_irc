/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_command.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:32:19 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/12 12:21:52 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	user_command(std::string args, Server &server, user &user)
{
	(void)server;
	user.set_username(args);
}
