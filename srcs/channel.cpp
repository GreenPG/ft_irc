/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:30:55 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/13 17:41:14 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/irc.hpp"

Channel::Channel()
{
	return ;
}

Channel::~Channel()
{
	return ;
}

void	Channel::add_user_to_channel(User &user)
{
	std::size_t		i;

	i = 0;
	while (i < _user_list.size())
	{
		if (_user_list[i].get_nickname() == user.get_nickname())
			return ;
		i++;
	}
	_user_list.insert(_user_list.end(), user);
}

void	Channel::add_user_as_operator(User &user)
{
	std::size_t		i;

	i = 0;
	while (i < _operator_list.size())
	{
		if (_operator_list[i].get_username() == user.get_username())
			return ;
		i++;
	}
	_operator_list.insert(_operator_list.end(), user);
}

void	Channel::kick_user_from_channel(std::vector<User> list, std::string user)
{
	std::size_t					i;
	std::vector<User>::iterator	it;

	it = list.begin();
	i = 0;
	while (i < list.size())
	{
		if (list[i].get_username() == user)
		{
			list.erase(it);
			return ;
		}
		it++;
		i++;
	}
}

void	Channel::print_every_user()
{
	std::size_t	i;

	i = 0;
	while (i < _user_list.size())
	{
		std::cout << _user_list[i].get_nickname() << std::endl;
		i++;
	}
}

int		Channel::is_user_op(std::string name)
{
	std::size_t						i;

	i = 0;
	while (i < _operator_list.size())
	{
		if (_operator_list[i].get_nickname() == name)
			return (0);
		i++;
	}
	return (1);
}

int	Channel::is_user_in_channel(std::string name)
{
	std::size_t						i;

	i = 0;
	while (i < _user_list.size())
	{
		if (_user_list[i].get_nickname() == name)
			return (0);
		i++;
	}
	return (1);
}

int		Channel::send_message_to_channel(std::string msg, Server *server)
{
	std::size_t	i;

	i = 0;
	while (i < _user_list.size() && search_user_by_nickname(server->getUserList(), _user_list[i].get_nickname()) != NULL)
	{
		sendMessage(msg.c_str(), *search_user_by_nickname(server->getUserList(), _user_list[i].get_nickname()));
		i++;
	}
	return (0);
}

void Channel::set_channel_name(std::string s)
{
	_channel_name = s;
}

void Channel::set_password(std::string s)
{
	_password = s;
}

std::string Channel::get_channel_name()
{
	return (_channel_name);
}

std::string Channel::get_password()
{
	return (_password);
}

std::vector<User>	Channel::get_chan_user_list()
{
	return (_user_list);
}


std::vector<User>	Channel::get_chan_op_list()
{
	return (_operator_list);
}
