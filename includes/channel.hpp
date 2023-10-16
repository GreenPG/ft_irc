/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:27:50 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/16 16:20:44 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "../includes/irc.hpp"
class	Server;
class	User;

class Channel
{
	public :
						Channel();
						~Channel();

	void				add_user_to_channel(User &user);
	void				kick_user_from_channel(std::vector<User> list, std::string user);
	void				add_user_as_operator(User &user);
	void				add_user_as_invited(User &user);
	void				del_invited_user(std::string nick);
	int					is_user_op(std::string name);
	int					is_user_in_channel(std::string name);
	int					is_user_invited(std::string nick);

	void				print_every_user();
	int					send_message_to_channel(std::string msg, Server *server);

	std::string			&get_channel_name();
	std::string			&get_password();
	std::string			&get_topic();
	std::vector<User>	&get_chan_user_list();
	std::vector<User>	&get_chan_op_list();
	bool				&get_invite_only();

	void				set_channel_name(std::string s);
	void				set_password(std::string s);
	void				set_topic(std::string s);
	void				set_invite_only(bool b);

	private :
    std::vector<User>	_user_list;
    std::vector<User>	_operator_list;
	std::vector<User>	_invite_list;
	std::string			_channel_name;
	std::string			_password;
	std::string			_topic;
	bool				_invite_only;

};

#endif
