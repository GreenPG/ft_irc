/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:25:25 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/19 15:46:59 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

bot::bot()
{
	std::string s;

	s = JOKE1();
	_tab.push_back(s);
	s = JOKE2();
	_tab.push_back(s);
	s = JOKE3();
	_tab.push_back(s);
	s = JOKE4();
	_tab.push_back(s);
	s = JOKE5();
	_tab.push_back(s);
	s = JOKE6();
	_tab.push_back(s);
	s = JOKE7();
	_tab.push_back(s);
	s = JOKE8();
	_tab.push_back(s);
	s = JOKE9();
	_tab.push_back(s);
	s = JOKE10();
	_tab.push_back(s);
	s = JOKE11();
	_tab.push_back(s);
	s = JOKE12();
	_tab.push_back(s);
	s = JOKE13();
	_tab.push_back(s);
	s = JOKE14();
	_tab.push_back(s);
	s = JOKE15();
	_tab.push_back(s);
	s = JOKE16();
	_tab.push_back(s);
	s = JOKE17();
	_tab.push_back(s);
	s = JOKE18();
	_tab.push_back(s);
	s = JOKE19();
	_tab.push_back(s);
	s = JOKE20();
	_tab.push_back(s);
	s = JOKE21();
	_tab.push_back(s);
	s = JOKE22();
	_tab.push_back(s);
}

bot::~bot()
{
}
