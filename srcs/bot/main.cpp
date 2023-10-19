/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:14:27 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/19 15:56:59 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <string>
#include <iostream>
#include "joke_database.hpp"
#include "bot.hpp"
#include <sys/time.h>
#include <vector>

static void	make_joke(std::string msg);
static void	send_random_joke(std::string user, std::string chan);

int	main(int argc, char **argv) {
	if (argc < 1)
		return (0);
	make_joke(argv[1]);	
}
//:DUDE PRIVMSG bot !joke					//priv
//:DUDE PRIVMSG #CHAN !joke					//chan
void	make_joke(std::string msg)
{
	std::string	user;
	std::string	chan;

	msg.erase(msg.begin(), msg.begin() + 1);

	user = msg.substr(0, msg.find(' '));
	msg.erase(msg.begin(),msg.begin() + msg.find(' ') + 1);
	msg.erase(msg.begin(),msg.begin() + msg.find(' ') + 1);
	chan = msg;
	chan = chan.substr(0, chan.find(' '));
	msg.erase(msg.begin(),msg.begin() + msg.find(' ') + 1);
	if (msg == "!joke")
		send_random_joke(user, chan);
	// std::cout << msg << "\n" << std::endl;
	// std::cout << user << "\n" << std::endl;
	// std::cout << chan << "\n" << std::endl;
}

void	send_random_joke(std::string user, std::string chan)
{
	struct timeval				time;
	int							i;
	bot							bott;

	gettimeofday(&time, NULL);
	i = time.tv_usec % 21 + 1;

	std::cout << "hey " << user << "\n"	<< std::endl;
	std::cout << bott._tab[i].substr(0, bott._tab[i].find('\n') + 1) << std::endl;
	std::cout << bott._tab[i].substr(bott._tab[i].find('\n') + 1, bott._tab[i].size()) << std::endl;
	(void)user;
	(void)chan;
}
