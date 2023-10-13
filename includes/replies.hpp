/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:43:58 by gpasquet          #+#    #+#             */
/*   Updated: 2023/10/13 10:29:14 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
# define REPLIES_HPP


#define	RPL_PRIVMSG(sender, target, msg) (":" + sender + " PRIVMSG " + target + " :" + msg + "\r\n")

//////////////////////////////RPL MESSAGES///////////////////////////////////////////////////
# define RPL_WELCOME(nick, user) ("001 " + nick " :Welcome to the ircserv Network, " + nick + "!" + user)
# define RPL_NOTOPIC(nick, channel) ("331 " + nick + " " + channel + " :No topic is set")
# define RPL_TOPIC(nick, channel, topic) ("332 " + nick + " " + channel + " :" + topic)
# define RPL_INVITING(nick, invited, channel) ("341 " + nick + " " + invited + " " + channel)
# define RPL_NAMREPLY(nick, channel, prefix, member) ("352 " + nick + " " + "#" + channel + " : " + prefix + member)
# define RPL_ENDOFNAMES(nick, channel) ("366 " + nick + " " + channel + " :End of /NAMES list")



///////////////////////////////ERRORS MESSAGES/////////////////////////////////////////////
# define ERR_NOSUCHNICK(nick, name) ("401 " + nick + " " + name + " :No such nick/channel")
# define ERR_NOSUCHCHANNEL(nick, channel) ("403 " + nick + " " + channel + " :No such channel")
# define ERR_CANNOTSENDTOCHAN(nick, channel) ("404 " + nick + " " + channe  " :Cannot send to channel")
# define ERR_BADCHANNELKEY(nick, channel) ("405 " + nick + " " + channel + " :Cannot join channel (+k)")
# define ERR_NORECIPIENT(nick, cmd) ("411 " + nick + " :No recipient given (" + cmd + ")" )
# define ERR_NOTEXTTOSEND(nick) ("412 " + nick + " :No text to send")
# define ERR_NONICKNAMEGIVEN(nick) ("431 " + nick " :No nickname given")
# define ERR_ERRONEUSNICKNAME(oldNick, newNick) ("432 " + oldNick + " " + newNick " :Erroneus nickname")
# define ERR_NICKNAMEINUSE(oldNick, newNick) ("433 " + oldNick + " " newNick + " :Nickname is already in use")
# define ERR_USERNOTINCHANNEL(nick, target, channel) ("441 " + nick + " " + target + " " + channel + " :They aren't on that channel" )
# define ERR_NOTONCHANNEL(nick, channel) ("442 " + nick + " " + channel + " :You're not ont that channel")
# define ERR_USERONCHANNEL(nick, invited, channel) ("443 " + nick + " " + invited + " " + channel + " :is already on channel")
# define ERR_CHANOPRIVSNEEDED(nick, channel) ("482 " + nick + " " + channel + " :You're not channel operator")
# define ERR_NEEDMOREPARAMS(nick, cmd) ("461 " + nick + cmd + " : Not enough parameters")
# define ERR_ALREADYREGISTERED(nick) ("462 " + nick + " : You may not be reregister")
# define ERR_PASSWDMISMATCH(nick) ("464 " + nick + "Password incorrect")
# define ERR_CHANNELISFULL(nick, channel) ("471 " + nick + " " + channel + " :Cannot join channel (+l)")
# define ERR_INVITEONLYCHAN(nick, channel) ("473 " + nick + " " + channel " :Cannot join channel (+i)")


#endif
