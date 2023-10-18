/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:27:50 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/18 14:15:10 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef USER_HPP
# define USER_HPP

# include "../includes/irc.hpp"

class User
{
	public :
						User();
						~User();

	bool				check_register();

	int					get_fd_socket();
	std::string			get_nickname();
	std::string			get_username();
	std::string			get_realname();
	int					get_password_check();
	bool				checkNick();
	bool				checkUser();

	void				set_fd_socket(int &fd);
	void				set_nickname(std::string s);
	void				set_username(std::string s);
	void				set_realname(std::string s);
	void				set_password_check();

	private :

	int					_password_check; // -1 if not check || 0 if checked
	int					_fd_socket;
	std::string			_nickname;
	std::string			_username;
	std::string			_realname;
	bool				_nickInit;
	bool				_userInit;

};
#endif
