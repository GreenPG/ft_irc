/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:30:55 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/09 16:56:17 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "channel.hpp"

channel::channel()
{
	return ;
}

channel::~channel()
{
	return ;
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