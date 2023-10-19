/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:27:14 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/19 15:56:38 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <string>
#include "joke_database.hpp"

# ifndef BOT_CPP
# define BOT_CPP

class bot
{
public:
											bot();
											~bot();
	std::vector<std::string>	 		_tab;
};
#endif
