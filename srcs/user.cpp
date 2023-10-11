/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:30:55 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/11 16:38:37 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/irc.hpp"

user::user()
{
	return ;
}

user::~user()
{
	return ;
}

int		user::check_register()
{
	if (_password == "")
		return (1);
	if (_nickname == "")
		return (2);
	if (_username == "")
		return (3);
	return (0);
}

void	user::register_user(char *s)
{
	int i;

	i = check_register();
	if (i == 1)
	{
		_password = s;
		send(_fd_socket, "Send nickname now dude\n", 24, 0);
		std::cout << "Receved password from " << _fd_socket << "\n" << std::endl;
	}

	if (i == 2)
	{
		_nickname = s;
		send(_fd_socket, "Send username now comrade\n", 27, 0);
	}
	if (i == 3)
	{
		_username = s;
		send(_fd_socket, "You are now registered\n", 24, 0);
		std::cout << "User " << _fd_socket << " is registered\n" << _password + "\n" << _nickname + "\n" << _username + "\n" << std::endl;
	}
}

user	*search_user_by_socket(std::vector<user> &user_list, const int fd)
{
	std::vector<user>::iterator	list;
	std::size_t						i;

	i = 0;
	list = user_list.begin();
	while (i < user_list.size())
	{
		if (list[i].get_fd_socket() == fd)
			return (&list[i]);
		i++;
	}
	return (&list[i]);
}

user	*search_user_by_nickname(std::vector<user> *user_list, std::string name)
{
	std::vector<user>::iterator	list;
	std::size_t						i;

	i = 0;
	list = user_list->begin();
	while (i < user_list->size())
	{
		if (list[i].get_nickname() == name)
			return (&list[i]);
		i++;
	}
	return (&list[i]);
}


void	user::set_fd_socket(int &fd)
{
	_fd_socket = fd;
}

void user::set_nickname(std::string s)
{
	_nickname = s;
}

void user::set_username(std::string s)
{
	_username = s;
}

void user::set_password(std::string s)
{
	_password = s;
}

int	user::get_fd_socket(void)
{
	return (_fd_socket);
}

std::string user::get_nickname()
{
	return (_nickname);
}

std::string user::get_username()
{
	return (_username);
}

std::string user::get_password()
{
	return (_password);
}
