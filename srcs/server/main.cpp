/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:16:22 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/20 13:58:23 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

int main(int argc, char **argv) {
	Server	server;	

	if (check_args(argc, argv) == 1)
		return (1);
	server.setPassword(argv[2]);
	if (server.initServer(argv[1]) == 1)
		return (1);
	server.listenLoop();
	return (0);
}
