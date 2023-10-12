/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:32:19 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/12 12:20:14 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	pass(std::string args, Server &server, user &user)
{
	(void)server;
	user.set_password(args);
}
