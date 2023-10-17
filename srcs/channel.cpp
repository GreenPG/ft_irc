/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:30:55 by tlarraze          #+#    #+#             */
/*   Updated: 2023/10/17 16:41:28 by tlarraze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/irc.hpp"

Channel::Channel()
{
	_channel_name = "";
	_password = "";
	_topic = "";
	_limit = -1;
	return ;
}

Channel::~Channel()
{
	return ;
}

void	Channel::add_user_to_channel(User &user)
{
	std::size_t		i;

	i = 0;
	while (i < _user_list.size())
	{
		if (_user_list[i].get_nickname() == user.get_nickname())
			return ;
		i++;
	}
	_user_list.insert(_user_list.end(), user);
}

void	Channel::add_user_as_operator(User &user)
{
	std::size_t		i;

	i = 0;
	while (i < _operator_list.size())
	{
		if (_operator_list[i].get_nickname() == user.get_nickname())
			return ;
		i++;
	}
	_operator_list.insert(_operator_list.end(), user);
}

void	Channel::add_user_as_invited(User &user) {
	for(size_t i = 0; i < _invite_list.size(); i++) {
		if (_invite_list[i].get_nickname() == user.get_nickname())
			return ;
	}
	_invite_list.push_back(user);
}

void	Channel::kick_user_from_channel(std::vector<User> &list, std::string user)
{
	std::size_t					i;

	i = 0;
	while (i < list.size())
	{
		std::cout << list[i].get_nickname() << "  " << user << std::endl;
		if (list[i].get_nickname() == user)
		{
			std::cout << "yep\n" << std::endl;
			list.erase(list.begin() + i);
			return ;
		}
		i++;
	}

}

void	Channel::print_every_user()
{
	std::size_t	i;

	i = 0;
	while (i < _user_list.size())
	{
		std::cout << _user_list[i].get_nickname() << std::endl;
		i++;
	}
}

int		Channel::is_user_op(std::string name)
{
	std::size_t						i;

	i = 0;
	while (i < _operator_list.size())
	{
		if (_operator_list[i].get_nickname() == name)
			return (0);
		i++;
	}
	return (1);
}

int	Channel::is_user_in_channel(std::string name)
{
	std::size_t						i;

	i = 0;
	while (i < _user_list.size())
	{
		if (_user_list[i].get_nickname() == name)
			return (0);
		i++;
	}
	return (1);
}

int	Channel::is_user_invited(std::string nick) {
	for (size_t i = 0; i < _invite_list.size(); i++) {
		if (_invite_list[i].get_nickname() == nick)
			return (0);
	}
	return (1);
}

bool	Channel::is_mode_active(modes_t mode)  {
	for (size_t i = 0; i < _modes.size(); i++) {
		if (_modes[i] == mode)
			return (true);
	}
	return (false);
}

int		Channel::send_message_to_channel(std::string msg)
{
	std::size_t	i;

	i = 0;
	while (i < _user_list.size())
	{
		sendMessage(msg.c_str(), _user_list[i]);
		i++;
	}
	return (0);
}

int		get_chan_pos(std::vector<Channel *> *channel_list, Channel *chan)
{
	size_t					i;
	std::vector<Channel *>	channelList = *channel_list;

	i = 0;
	while (i < channelList.size())
	{
		if (chan->get_channel_name() == channelList[i]->get_channel_name())
			return (i);
		i++;
	}
	return (-1);
}

void Channel::set_channel_name(std::string s)
{
	_channel_name = s;
}

void Channel::set_password(std::string s)
{
	_password = s;
}

void Channel::set_topic(std::string s)
{
	_topic = s;
}

void				Channel::set_limit(int limit) {
	_limit = limit;
}

void				Channel::add_mode(modes_t newMode) {
	for (size_t i = 0; i < _modes.size(); i++) {
		if (_modes[i] == newMode)
			return ;
	}
	_modes.push_back(newMode);
}

void				Channel::delete_mode(modes_t mode) {
	std::vector<modes_t>::iterator	it = _modes.begin();

	while (it != _modes.end()) {
		if (*it == mode) {
			_modes.erase(it);
			return ;
		}
	}
}

std::string &Channel::get_channel_name()
{
	return (_channel_name);
}

std::string &Channel::get_password()
{
	return (_password);
}

std::string	&Channel::get_topic()
{
	return (_topic);
}
std::vector<User>	&Channel::get_chan_user_list()
{
	return (_user_list);
}

std::vector<User>	&Channel::get_chan_op_list()
{
	return (_operator_list);
}

std::string			Channel::get_mode_list() {
	std::string modeList;

	for (size_t i = 0; i < _modes.size(); i++) {
		switch (_modes[i]) {
			case INVITE:
				modeList.append("i");
				break;
			case TOPIC:
				modeList.append("t");
				break;
			case KEY:
				modeList.append("k");
				break;
			case LIMIT:
				modeList.append("l");
				break;
		}
	}
	return (modeList);
}

int					Channel::get_limit() {
	return (_limit);
}
