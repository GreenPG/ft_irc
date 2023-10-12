/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:14:15 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/12 12:25:10 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	cap(std::string args, Server &server, user &currentUser) {
	(void)server;
	(void)args;
	sendMessage("CAP * LS :", currentUser);
}
