/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:30:55 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/12 16:12:17 by tlarraze         ###   ########.fr       */
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

int		user::check_register()
{
	if (_nickname == "")
		return (1);
	if (_username == "")
		return (2);
	return (0);
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

user	*search_user_by_nickname(std::vector<user> &user_list, std::string name)
{
	std::vector<user>::iterator	list;
	std::size_t						i;

	i = 0;
	list = user_list.begin();
	while (i < user_list.size())
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

void	user::set_password_check()
{
	_password_check = 0;
}

int		user::get_password_check()
{
	return (_password_check);
}