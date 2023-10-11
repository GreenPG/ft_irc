/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:30:55 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/11 16:20:25 by tlarraze         ###   ########.fr       */
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

void	channel::add_user_to_channel(std::string user)
{
	std::size_t		i;

	i = 0;
	while (i < _user_list.size())
	{
		if (_user_list[i] == user)
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
		std::cout << _user_list[i] << std::endl;
		i++;
	}
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
