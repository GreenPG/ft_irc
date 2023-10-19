/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:16:22 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/19 14:22:45 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

int main(int argc, char **argv) {
	Server	server;	

	if (check_args(argc, argv) == 1)
		return (1);
	server.setPassword(argv[2]);
	server.initServer(argv[1]);
	server.listenLoop();
	return (0);
}
