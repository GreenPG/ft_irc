/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:32:19 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/12 15:33:57 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	pass(std::string args, Server &server, user &user)
{
	if (user.get_password_check() == 0)
		sendMessage("ERR_ALREADYREGISTERED\n", user);
	else if (args != server.getPassword())
	{
		sendMessage(ERR_PASSWDMISMATCH(user.get_nickname()).c_str(), user);
		return ;
	}
	else if (user.get_password_check() != 0)
		user.set_password_check();
}
