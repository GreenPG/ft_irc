/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:27:50 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/11 14:59:20 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "../includes/irc.hpp"

class channel
{
	public :
						channel();
						~channel();

	void				add_user_to_channel(std::string user);

	void				print_every_user();
	std::string			get_channel_name();
	std::string			get_password();

	void				set_channel_name(std::string s);
	void				set_password(std::string s);

	private :
    std::vector<std::string>	_user_list;
	std::string					_channel_name;
	std::string					_password;
//	int							_invite_only;

};

#endif
