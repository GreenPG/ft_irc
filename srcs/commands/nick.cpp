/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:32:19 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/12 12:20:46 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	nick(std::string args, Server &server, user &user)
{
	(void)server;
    std::cout << args << "dwqdwq" << std::endl;
	user.set_nickname(args);
}
