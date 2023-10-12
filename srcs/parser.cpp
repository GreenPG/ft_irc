/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:33:01 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/12 10:20:26 by gpasquet         ###   ########.fr       */
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

void	parser(const std::string &input, std::vector<channel> &channel_list, user &currentUser) {
	std::vector<std::string>	cmdList;
	std::string 				cmd;
	std::string					args;
	unsigned int				j; 
	int							spaceIdx;

	const std::string			cmdArr[] = {"CAP", "PASS", "NICK", "USER", "PRIVMSG", "JOIN", "MODE", "INVITE", "TOPIC", "KICK"};
	std::vector<std::string> 	cmdsVec(cmdArr, cmdArr + sizeof(cmdArr) / sizeof(cmdArr[0]));
	cmdFunctions				cmdFunctions[] = {&cap, &pass, &nick, &user_command, &privmsg, &join,  &mode, &invite, &topic, &kick};
	cmdList = splitInput(input);
	for (unsigned int i = 0; i < cmdList.size(); i++) {
		spaceIdx = cmdList[i].find(' ');
		cmd = cmdList[i].substr(0, spaceIdx);
		args = cmdList[i].substr(spaceIdx + 1, input.size() - spaceIdx);
			std::cout << "command " << cmdsVec[i] << " from socket: " << currentUser.get_fd_socket() << ", nick: " << currentUser.get_nickname() << std::endl;
		std::cout << args << '\n' << "TTTTTTTTTTTTTT" << std::endl;
		for (j = 0; j < cmdsVec.size(); j++) { 
			if (cmdsVec[i] == "JOIN") {
				join(args, channel_list, currentUser);
				break;
			}
			if (cmdsVec[i] == "PASS") {
				pass(args, currentUser);
				break;
			}
			if (cmdsVec[i] == "NICK") {
				nick(args, currentUser);
				break;
			}
			if (cmdsVec[i] == "USER") {
				user_command(args, currentUser);
				break;
			}
			if (cmdsVec[i] == "CAP") {
				cap(currentUser);
				break;
			}
		}
		if (j == cmdsVec.size())
			std::cout << "Unknown command" << std::endl;
	}
}
