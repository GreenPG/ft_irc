/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:14:27 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/20 13:30:22 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/bot.hpp"

int	main(void) {
	Bot	bot;

	bot.initSocket();
	bot.loginToServ();
	bot.readLoop();
	return (0);
}
