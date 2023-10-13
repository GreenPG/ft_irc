/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:27:50 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/13 14:00:29 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "../includes/irc.hpp"
class	Server;

class channel
{
	public :
						channel();
						~channel();

	void				add_user_to_channel(user &user);
	void				print_every_user();
	int					send_message_to_channel(std::string msg, Server *server);

	std::string			get_channel_name();
	std::string			get_password();

	void				set_channel_name(std::string s);
	void				set_password(std::string s);

	private :
    std::vector<user>	_user_list;
	std::string			_channel_name;
	std::string			_password;
//	int					_invite_only;

};

#endif
