/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:34:54 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/19 14:25:21 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

int is_num(std::string s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] < '0' || s[i] > '9')
            return (1);
        i++;
    }
    return (0);
}

int check_args(int argc, char **argv)
{
	if (argc == 2) {
		std::cout << "Port number expected" << std::endl;
		return (1);
	}
    if (argc != 3) {
		std::cout << "Wrong number of args  \"./ircserv <port> <password>\"" << std::endl;
        return (1);
    }
    if (is_num(argv[1]) == 1) {
		std::cout << "Port can only be numbers" << std::endl;
        return (1);
    }
    return (0);
}
