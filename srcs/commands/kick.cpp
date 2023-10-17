/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:03:43 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/17 14:33:18 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	kick(std::string args, Server &server, User &user) {
	std::string		channel_arg;
	std::string		user_arg;
	std::string		msg_arg;
	Channel			*chan;
	size_t			i;
	
	i = 0;
	channel_arg = args;
	user_arg = args;
	channel_arg.resize(channel_arg.find(' ', 0));
	user_arg.erase(0, user_arg.find(' ', 0) + 1);
	msg_arg = user_arg;
	if (user_arg.find(' ', 0) != std::string::npos)
	{
		msg_arg.erase(0, msg_arg.find(' ', 0) + 1);
		user_arg.resize(user_arg.find(' ', 0));
	}
	else
		msg_arg = "";
	chan = search_channel_by_name(server.getChannelList(), channel_arg);
	if (chan == NULL)
	{
		std::cout << "t" << channel_arg << "t" << std::endl;
		sendMessage(ERR_NOSUCHCHANNEL(user.get_nickname(), channel_arg).c_str(), user);
		return ;
	}
	else if (chan->is_user_in_channel(user_arg) != 0)
	{
		sendMessage(ERR_USERNOTINCHANNEL(user.get_nickname(), user_arg, channel_arg).c_str(), user);
		return ;
	}
	else if (chan->is_user_op(user.get_nickname()) != 0)
	{
		sendMessage(ERR_CHANOPRIVSNEEDED(user.get_nickname(), channel_arg).c_str(), user);
		return ;
	}
	while (i < chan->get_chan_user_list().size())
	{
		if (msg_arg == "")
			sendMessage(RPL_KICK(user_arg, channel_arg).c_str(), chan->get_chan_user_list()[i]);
		else
			sendMessage(RPL_KICK_REASON(user_arg, channel_arg, msg_arg).c_str(), chan->get_chan_user_list()[i]);
		i++;
	}
	chan->kick_user_from_channel(chan->get_chan_user_list(), user_arg);
	chan->kick_user_from_channel(chan->get_chan_op_list(), user_arg);
	if (chan->get_chan_user_list().size() == 0 && get_chan_pos(server.getChannelList(), chan) != -1)
	{
		delete	chan;
		server.getChannelList()->erase(server.getChannelList()->begin() + get_chan_pos(server.getChannelList(), chan));
	}
	// std::cout << "NEED TO ADD MESSAGE, DIDNT HAVE TIME LAST TIME SORRY" << args << "\n" << std::endl;


	// std::cout << "FULL ARGS " << args << "\n" << std::endl;
	// std::cout << "CHANNEL ARGS " << channel_arg << "\n" << std::endl;
	// std::cout << "USER ARGS " << user_arg << "\n" << std::endl;
	// std::cout << "MSG ARGS " << msg_arg << "\n" << std::endl;
}
