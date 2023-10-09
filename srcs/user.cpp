/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:30:55 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/09 17:29:20 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/user.hpp"

user::user()
{
	return ;
}

user::~user()
{
	return ;
}

void	user::set_fd_socket(int fd)
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
