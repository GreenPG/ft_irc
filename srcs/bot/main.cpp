/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:14:27 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/20 13:45:48 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/bot.hpp"

int	main(void) {
	Bot	bot;

	if (bot.initSocket() == 1)
		return (1);
	bot.loginToServ();
	bot.readLoop();
	return (0);
}
