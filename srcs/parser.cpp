/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:33:01 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/12 15:17:54 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

static std::vector<std::string>	splitInput(std::string input) {
	size_t						end;
	size_t						start  = 0;
	std::vector<std::string>	cmdList;

	while (start < input.npos) {  
		end = input.find_first_of("\r\n", start);
		if (end != input.npos)
			cmdList.push_back(input.substr(start, end - start));
		start = input.find_first_not_of("\r\n", end);
	}
	return (cmdList);
}

void	parser(const std::string &input, Server &server, user &currentUser) {
	std::vector<std::string>	cmdList;
	std::string 				cmd;
	std::string					args;
	unsigned int				j; 
	int							spaceIdx;

	const std::string			cmdArr[] = {"CAP", "PASS", "NICK", "USER", "PRIVMSG", "JOIN", "MODE", "INVITE", "TOPIC", "KICK"};
	std::vector<std::string> 	cmdsVec(cmdArr, cmdArr + sizeof(cmdArr) / sizeof(cmdArr[0]));
	cmdFunctions				cmds[] = {&cap, &pass, &nick, &user_command, &privmsg, &join, &mode, &invite, &topic, &kick};

	cmdList = splitInput(input);
	for (unsigned int i = 0; i < cmdList.size(); i++) {
		spaceIdx = cmdList[i].find(' ');
		cmd = cmdList[i].substr(0, spaceIdx);
		args = cmdList[i].substr(spaceIdx + 1, input.size() - spaceIdx);
			std::cout << "command " << cmd << " from socket: " << currentUser.get_fd_socket() << ", nick: " << currentUser.get_nickname() << std::endl;
		for (j = 0; j < cmdsVec.size(); j++) { 
			if (cmdsVec[j] == cmd) {
				if (cmd == "PASS" || currentUser.get_password_check() == 0)
					(*cmds[j])(args, server, currentUser);
						break;
			}
		}
		if (j == cmdsVec.size() && currentUser.get_password_check() == 0)
			std::cout << "Unknown command" << std::endl;
	}
}
