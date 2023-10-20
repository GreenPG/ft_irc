/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:43:58 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/20 13:51:14 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
# define REPLIES_HPP


# define RPL_PRIVMSG(sender, target, msg) (":" + sender + " PRIVMSG " + target + " " + msg + "\r\n")
# define RPL_JOIN(joiner, channel) (":" + joiner + " JOIN " + channel + "\r\n")
# define RPL_KICK(nick, channel, kicked) (":" + nick + " KICK " + channel + " " + kicked + "\r\n")
# define RPL_KICK_REASON(nick, channel, kicked, reason) (":" + nick + " KICK " + channel + " " + kicked + " :" + reason + "\r\n")
# define RPL_NICK(oldNick, username, newNick) (":" + oldNick + "!" + username + " NICK :" + newNick + "\r\n")
# define MODE(nick, channel, modes, args) (":" + nick + " MODE " + channel + " " + modes + " " + args + "\r\n")
# define INVITE(nick, invited, channel)	(":" + nick + " INVITE " + invited + " " + channel + "\r\n")	

//////////////////////////////RPL MESSAGES///////////////////////////////////////////////////
# define RPL_WELCOME(nick, user) (": 001 " + nick +  " :Welcome to the ircserv Network, " + nick + "!" + user + "\r\n")
# define RPL_CHANNELMODEIS(nick, channel, modes, args) (": 324 " + nick + " " + channel + " " + modes + " " + args + "\r\n")
# define RPL_NOTOPIC(nick, channel) (": 331 " + nick + " " + channel + " :No topic is set" + "\r\n")
# define RPL_TOPIC(nick, channel, topic) (": 332 " + nick + " " + channel + " " + topic + "\r\n")
# define RPL_INVITING(nick, invited, channel) (": 341 " + nick + " " + invited + " " + channel + "\r\n")
# define RPL_NAMREPLY(nick, channel, memberList) (": 353 " + nick + " = " + channel + " :" + userList + "\r\n")
# define RPL_ENDOFNAMES(nick, channel) (": 366 " + nick + " " + channel + " :End of /NAMES list" + "\r\n")
# define RPL_QUIT(nick, reason) (":" + nick + " QUIT :" + reason + "\r\n")


///////////////////////////////ERRORS MESSAGES/////////////////////////////////////////////


# define ERR_NOSUCHNICK(nick, name) (": 401 " + nick + " " + name + " :No such nick/channel" + "\r\n")
# define ERR_NOSUCHCHANNEL(nick, channel) (": 403 " + nick + " " + channel + " :No such channel" + "\r\n")
# define ERR_CANNOTSENDTOCHAN(nick, channel) (": 404 " + nick + " " + channel + " :Cannot send to channel" + "\r\n")
# define ERR_BADCHANNELKEY(nick, channel) (": 405 " + nick + " " + channel + " :Cannot join channel (+k)" + "\r\n")
# define ERR_NORECIPIENT(nick, cmd) (": 411 " + nick + " :No recipient given (" + cmd + ")"  + "\r\n")
# define ERR_NOTEXTTOSEND(nick) (": 412 " + nick + " :No text to send" + "\r\n")
# define ERR_UNKNOWNCOMMAND(nick, cmd) (": 421 " + nick + " " + cmd + " :Unknown command\r\n")
# define ERR_NONICKNAMEGIVEN(nick) (": 431 " + nick + " :No nickname given" + "\r\n")
# define ERR_ERRONEUSNICKNAME(oldNick, newNick) (": 432 " + oldNick + " " + newNick + " :Erroneus nickname" + "\r\n")
# define ERR_NICKNAMEINUSE(oldNick, newNick) (": 433 " + oldNick + " " + newNick + " :Nickname is already in use" + "\r\n")
# define ERR_USERNOTINCHANNEL(nick, target, channel) (": 441 " + nick + " " + target + " " + channel + " :They aren't on that channel"  + "\r\n")
# define ERR_NOTONCHANNEL(nick, channel) (": 442 " + nick + " " + channel + " :You're not ont that channel" + "\r\n")
# define ERR_USERONCHANNEL(nick, invited, channel) (": 443 " + nick + " " + invited + " " + channel + " :is already  on channel\r\n")
# define ERR_NOTREGISTERED(nick) (":451 " + nick + " :You have not registered\r\n")
# define ERR_NEEDMOREPARAMS(nick, cmd) (": 461 " + nick + " " + cmd + " : Not enough parameters" + "\r\n")
# define ERR_ALREADYREGISTERED(nick) (": 462 " + nick + " : You may not reregister" + "\r\n")
# define ERR_PASSWDMISMATCH(nick) (": 464 " + nick + "Password incorrect" + "\r\n")
# define ERR_CHANNELISFULL(nick, channel) (": 471 " + nick + " " + channel + " :Cannot join channel (+l)" + "\r\n")
# define ERR_INVITEONLYCHAN(nick, channel) (": 473 " + nick + " " + channel + " :Cannot join channel (+i)" + "\r\n")
# define ERR_BADCHANMASK(nick, channel) (": 476 " + nick + " " + channel + " :Bad Channel Mask" + "\r\n")
# define ERR_CHANOPRIVSNEEDED(nick, channel) (": 482 " + nick + " " + channel + " :You're not channel operator" + "\r\n")
# define ERR_UMODEUNKNOWNFLAG(nick, flag) (": 501 " + nick + " :Unknown MODE flag :" + flag + "\r\n")
# define ERR_INVALIDMODEPARAM(nick, channel, modeChar, parameter, description) (": 696 " + nick + " " + channel + " " + modeChar + " " + parameter +  " :" + description + "\r\n")
#endif
