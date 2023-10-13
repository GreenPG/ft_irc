/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:30:55 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/13 14:01:59 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/irc.hpp"

channel::channel()
{
	return ;
}

channel::~channel()
{
	return ;
}

void	channel::add_user_to_channel(user &user)
{
	std::size_t		i;

	i = 0;
	while (i < _user_list.size())
	{
		if (_user_list[i].get_username() == user.get_username())
			return ;
		i++;
	}
	_user_list.insert(_user_list.end(), user);
}



void	channel::print_every_user()
{
	std::size_t	i;

	i = 0;
	while (i < _user_list.size())
	{
		std::cout << _user_list[i].get_username() << std::endl;
		i++;
	}
}

int		channel::send_message_to_channel(std::string msg, Server *server)
{
	std::size_t	i;

	i = 0;
	while (i < _user_list.size())
	{
		sendMessage(msg.c_str(), *search_user_by_nickname(server->getUserList(), _user_list[i].get_username()));
		i++;
	}
	return (0);
}

void channel::set_channel_name(std::string s)
{
	_channel_name = s;
}

void channel::set_password(std::string s)
{
	_password = s;
}

std::string channel::get_channel_name()
{
	return (_channel_name);
}

std::string channel::get_password()
{
	return (_password);
}
