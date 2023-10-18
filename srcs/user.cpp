/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:30:55 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/18 14:19:53 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../includes/irc.hpp"

User::User()
{
	_nickname = "*";
	_username = "*";
	_realname = "*";
	_password_check = -1;
	_nickInit = false;
	_userInit = false;
	return ;
}

User::~User()
{
	return ;
}

bool	User::check_register()
{
	if (_nickInit == false || _userInit == false || _password_check == -1) 
		return (false);
	return (true);
}

User	*search_user_by_socket(std::vector<User> &user_list, const int fd)
{
	std::vector<User>::iterator	list;
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

User	*search_user_by_nickname(std::vector<User> *user_list, std::string name)
{
	std::vector<User>::iterator	list;
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

void	User::set_fd_socket(int &fd)
{
	_fd_socket = fd;
}

void User::set_nickname(std::string s)
{
	_nickname = s;
}

void User::set_username(std::string s)
{
	_username = s;
}

void User::set_realname(std::string s)
{
	_realname = s;
}

int	User::get_fd_socket(void)
{
	return (_fd_socket);
}

std::string User::get_nickname()
{
	return (_nickname);
}

std::string User::get_username()
{
	return (_username);
}

std::string User::get_realname()
{
	return (_realname);
}

bool		User::checkNick() {
	return (this->_nickInit);
}

bool		User::checkUser() {
	return (this->_userInit);
}

void	User::set_password_check()
{
	_password_check = 0;
}

int		User::get_password_check()
{
	return (_password_check);
}
