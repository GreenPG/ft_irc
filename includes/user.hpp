/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:27:50 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/12 14:16:12 by tlarraze         ###   ########.fr       */
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

	int					get_fd_socket();
	std::string			get_nickname();
	std::string			get_username();
	int					get_password_check();

	void				set_fd_socket(int &fd);
	void				set_nickname(std::string s);
	void				set_username(std::string s);
	void				set_password_check();

	private :

	int					_password_check; // -1 if not check || 0 if checked
	int					_fd_socket;
	std::string			_nickname;
	std::string			_username;

};
#endif
