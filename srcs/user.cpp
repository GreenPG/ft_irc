/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:30:55 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/13 15:46:40 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/irc.hpp"

user::user()
{
	_password_check = -1;
	return ;
}

user::~user()
{
	return ;
}

bool	user::check_register()
{
	if (_nickname.empty() || _username.empty() || _password_check == -1) 
		return (false);
	return (true);
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
	return (NULL);
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

void user::set_realname(std::string s)
{
	_realname = s;
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

std::string user::get_realname()
{
	return (_realname);
}

void	user::set_password_check()
{
	_password_check = 0;
}

int		user::get_password_check()
{
	return (_password_check);
}
