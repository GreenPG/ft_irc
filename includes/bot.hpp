/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:27:14 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/20 12:19:09 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_CPP
# define BOT_CPP

# include <vector>
# include <string>
# include <sys/time.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <netdb.h>
# include <unistd.h>
# include <string>
# include <cstring>
# include <cstdlib>
# include <iostream>
 
# include "joke_database.hpp"

# define	NICK_QUERY(nick) ("NICK " + nick + "\r\nUSER Bot\r\n")
# define	PASS_QUERY(pass) ("PASS " + pass + "\r\n")
# define	JOIN_QUERY(chan) ("JOIN " + chan + "\r\n")
# define	KILL_MSG(nick) ("PRIVMSG" + nick + " JokeBot has been stopped\r\n")
# define	UNKNOWN_REPLY(nick) ("PRIVMSG " + nick + " JokeBot only understand !joke and !kill\r\n")

class Bot
{
	public:
		Bot();
		~Bot();

		int		initSocket();
		void	loginToServ() const;
		void	readLoop() const; 

	private:

		void		sendPass() const; 
		int 		sendNickAndUser() const;
		bool		parser(std::string buf) const;
		void		invite(std::string msg) const;
		void		killBot(std::string nick) const;
		bool		make_joke(std::string msg) const;
		int			sendMessage(const char *message) const;
		void		send_random_joke(std::string chan) const;
		std::string	get_start_message(std::string name) const;

		std::vector<std::string>	_tab;
		int							_socketFd;
};
#endif
