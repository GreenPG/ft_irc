/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:25:28 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/12 11:43:55 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CPP
# define SERVER_CPP

# include "irc.hpp"

class	Server 
{
	private:
		
		Server(const Server &copy);
		Server &operator=(const Server &copy);
		
		int						_listener;
		int						_fdMax;
		fd_set					_master;
		fd_set					_readFds;
		std::vector<user>		_userList;
		std::vector<channel>	_channelList;

		user	&identifyUser(const int userFd); 
		struct	addrinfo initHints(void);
		int		newConnection(void); 
		void	receiveError(const int &nbytes, int &socketFd); 
		void	receiveData(int &socketFd); 
		void	readLoop();

	public:
		
		Server();
		~Server();		

		int						&getListener();
		int						&getFdMax();
		fd_set					&getMaster();
		fd_set					&getReadFds();
		std::vector<user>		&getUserList();
		std::vector<channel>	&getChannelList();

		void					initServer(const char *portNb);
		void					listenLoop();
};

#endif