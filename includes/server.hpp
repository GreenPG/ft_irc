/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:25:28 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/18 16:58:59 by tlarraze         ###   ########.fr       */
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
		
		int						_quit;
		int						_listener;
		int						_fdMax;
		int						_userNb;
		fd_set					_master;
		fd_set					_readFds;
		std::string				_password;
		std::vector<User>		_userList;
		std::vector<Channel *>	_channelList;

		User	&identifyUser(const int userFd); 
		struct	addrinfo initHints(void);
		int		newConnection(void); 
		void	receiveError(const int &nbytes, int &socketFd); 
		void	receiveData(int &socketFd); 
		void	readLoop();

	public:

		Server();
		~Server();		

		int						getQuit();
		int						&getListener();
		int						&getFdMax();
		fd_set					&getMaster();
		fd_set					&getReadFds();
		std::string				&getPassword();
		std::vector<User>		*getUserList();
		std::vector<Channel *>	*getChannelList();

		void					setQuit();
		void					setPassword(std::string Pass);
		void					incUser();
		void					decUser();
		void					initServer(const char *portNb);
		void					listenLoop();
		void					sendMessageToServer(std::string msg);
		void					remove_every_trace_of_user(User *user);
};

#endif
