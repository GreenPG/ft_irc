/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:16:22 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/12 14:46:49 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

int main(int argc, char **argv) {
	Server	server;	

	if (argc != 2) {
		std::cout << "Port number expected" << std::endl;
		exit(1);
	}
	server.initServer(argv[1]);
	server.listenLoop();
	return (0);
}
