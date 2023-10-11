/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:27:50 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/11 16:02:32 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef USER_HPP
# define USER_HPP

# include "../includes/irc.hpp"

class user
{
	public :
						user();
						~user();

	int					check_register();
	void				register_user(char *s);

	int					get_fd_socket();
	std::string			get_nickname();
	std::string			get_username();
	std::string			get_password();

	void				set_fd_socket(int &fd);
	void				set_nickname(std::string s);
	void				set_username(std::string s);
	void				set_password(std::string s);

	private :

	int					_fd_socket;
	std::string			_nickname;
	std::string			_username;
	std::string			_password;

};
#endif
