/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:27:50 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/09 17:00:46 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string"
#include <vector>

class channel
{
	public :
						channel();
						~channel();

	std::string			get_channel_name();
	std::string			get_password();

	void				set_channel_name(std::string s);
	void				set_password(std::string s);

	private :
    std::vector<std::string>    user_list;
	std::string     			_channel_name;
	std::string		        	_password;

};