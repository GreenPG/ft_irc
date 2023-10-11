/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:33:01 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/11 15:58:26 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

void	parser(const std::string &input, std::vector<channel> *channel_list, user *user) {
	std::string cmd;
	std::string	args;
	unsigned	i; 

	int							spaceIdx;
	const std::string			cmdArr[] = {"PASS", "NICK", "USER", "PRIVMSG", "JOIN", "MODE", "INVITE", "TOPIC", "KICK"};
		std::vector<std::string> 	cmdsVec(cmdArr, cmdArr + sizeof(cmdArr) / sizeof(cmdArr[0]));

	spaceIdx = input.find(' ');
	cmd = input.substr(0, spaceIdx);
	std::cout << input << '\n' << std::endl;
	args = input.substr(spaceIdx + 1, input.size() - spaceIdx);
	std::cout << args << '\n' << "TTTTTTTTTTTTTT" << std::endl;
	for (i = 0; i < cmdsVec.size(); i++) { 
		if (cmdsVec[i] == cmd) {
			std::cout << "command " << cmdsVec[i] << " FROM " << user->get_fd_socket() << std::endl;
			if (cmdsVec[i] == "JOIN")
				join(args, channel_list, user);
			if (cmdsVec[i] == "PASS")
				pass(args, user);
			if (cmdsVec[i] == "NICK")
				nick(args, user);
			if (cmdsVec[i] == "USER")
				user_command(args, user);
			break;
		}
	}
	if (i == cmdsVec.size())
		std::cout << "Unknown command" << std::endl;
}
