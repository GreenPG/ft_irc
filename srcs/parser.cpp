/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:33:01 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/18 17:20:00 by gpasquet         ###   ########.fr       */
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

void	parser(const std::string &input, Server &server, User &currentUser) {
	std::vector<std::string>	cmdList;
	std::string 				cmd;
	std::string					args;
	static std::string			buf;
	unsigned int				j; 
	int							spaceIdx;

	const std::string			cmdArr[] = {"PASS", "NICK", "USER", "PRIVMSG", "JOIN", "MODE", "INVITE", "TOPIC", "KICK", "SQUIT"};
	std::vector<std::string> 	cmdsVec(cmdArr, cmdArr + sizeof(cmdArr) / sizeof(cmdArr[0]));
	cmdFunctions				cmds[] = {&pass, &nick, &user_command, &privmsg, &join, &mode, &invite, &topic, &kick, &squit};

	buf.append(input);
	if (buf[buf.size() - 1] == '\n') {
		cmdList = splitInput(buf);
		for (unsigned int i = 0; i < cmdList.size(); i++) {
			spaceIdx = cmdList[i].find(' ');
			cmd = cmdList[i].substr(0, spaceIdx);
			spaceIdx = cmdList[i].find_first_not_of(" ", spaceIdx); 
			if (spaceIdx == -1)
				args = "";
			else 
				args = cmdList[i].substr(spaceIdx, input.size() - spaceIdx);
			std::cout << "command " << cmd << " from socket: " << currentUser.get_fd_socket() << ", nick: " << currentUser.get_nickname() << std::endl;
			for (j = 0; j < cmdsVec.size(); j++) { 
				if (cmdsVec[j] == cmd) {
					if (currentUser.check_register() == true || cmd == "PASS")
						(*cmds[j])(args, server, currentUser);
					else if (currentUser.get_password_check() == 0 && (cmd == "NICK" || cmd == "USER")) 
						(*cmds[j])(args, server, currentUser);
					else
						sendMessage(ERR_NOTREGISTERED(currentUser.get_nickname()).c_str(), currentUser);
					break;
				}
			}
			if (j == cmdsVec.size() && cmd != "WHO" && cmd != "CAP")
				sendMessage(ERR_UNKNOWNCOMMAND(currentUser.get_nickname(), cmd).c_str(), currentUser);
		}
		buf.clear();
	}
}
