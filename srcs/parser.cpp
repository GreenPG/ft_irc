/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:33:01 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/10 16:22:43 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

void	parser(const std::string &input) {
	std::string cmd;
	std::string	args;
	unsigned	i; 

	int							spaceIdx;
	const std::string			cmdArr[] = {"PASS", "NICK", "USER", "PRIVMSG", "JOIN", "MODE", "INVITE", "TOPIC", "KICK"};
		std::vector<std::string> 	cmdsVec(cmdArr, cmdArr + sizeof(cmdArr) / sizeof(cmdArr[0]));

	spaceIdx = input.find(' ');
	cmd = input.substr(0, spaceIdx);
	args = input.substr(spaceIdx + 1, input.size() - spaceIdx);
	for (i = 0; i < cmdsVec.size(); i++) { 
		if (cmdsVec[i] == cmd) {
			std::cout << "command " << cmdsVec[i] << std::endl; 
			break;
		}
	}
	if (i == cmdsVec.size())
		std::cout << "Unknown command" << std::endl;
}
