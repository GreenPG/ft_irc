/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:14:15 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/13 17:06:52 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	cap(std::string args, Server &server, User &currentUser) {
	(void)server;
	(void)args;
	sendMessage("CAP * LS :", currentUser);
}
