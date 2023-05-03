/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorCodes.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:50:35 by ljourand          #+#    #+#             */
/*   Updated: 2022/11/21 11:47:26 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORCODES_HPP
# define ERRORCODES_HPP

# include <string>

class Server;
class User;
class Channel;

std::string RPL_WELCOME(const User &user);
std::string	RPL_LUSERCLIENT(const Server &server);
std::string RPL_LUSEROP(const Server &server);
std::string	RPL_LUSERCHANNELS(const Server &server);
std::string	RPL_LUSERME(const Server &server);
std::string RPL_MOTDSTART(const Server &server);
std::string RPL_MOTD(const std::string &line);
std::string RPL_ENDOFMOTD(void);
std::string RPL_NOTOPIC(Channel &channel, User &user);
std::string RPL_TOPIC(Channel &channel, User &user);
std::string RPL_NAMREPLY(Channel &channel, User &user);
std::string RPL_NAMREPLY(User &user, const std::string &nicknames);
std::string RPL_ENDOFNAMES(Channel &channel, User &user);
std::string RPL_ENDOFNAMES(User &user, const std::string &name = "");
std::string RPL_LIST(const Channel &channel, User &user);
std::string RPL_LIST_PRIV(const Channel &channel, User &user);
std::string RPL_LISTEND(User &user);
std::string RPL_INVITING(const std::string &channelName, const std::string &nickname);
std::string RPL_CREATED(void);
std::string RPL_MYINFO(const Server &server);
std::string	RPL_YOUREOPER(void);
std::string RPL_YOURHOST(const Server &server);
std::string RPL_UMODEIS(const User &user);
std::string RPL_CHANNELMODEIS(const Channel &channel);
std::string RPL_BANLIST(const Channel &channel, const std::string &banMask);
std::string RPL_ENDOFBANLIST(const Channel &channel);
std::string RPL_INVITELIST(const Channel &channel, const std::string &inviteMask);
std::string RPL_ENDOFINVITELIST(const Channel &channel);

std::string	ERR_NOTEXTTOSEND(void);
std::string	ERR_NONICKNAMEGIVEN(void);
std::string	ERR_ERRONEUSNICKNAME(const std::string &nickname);
std::string	ERR_NEEDMOREPARAMS(const std::string &cmdName);
std::string	ERR_ALREADYREGISTRED(void);
std::string	ERR_NOTREGISTERED(void);
std::string ERR_PASSWDMISMATCH(const std::string &password);
std::string	ERR_ERR_NICKNAMEINUSE(const std::string &nickname);
std::string ERR_NOSUCHNICK(const std::string &nickname);
std::string ERR_PINGTIMEOUT(void);
std::string ERR_INCORRECTEPINGREPLY(void);
std::string ERR_BADCHANMASK(const std::string &nickClient, const std::string &channelName);
std::string ERR_NOTONCHANNEL(const std::string &channelName);
std::string ERR_NOSUCHCHANNEL(const std::string &channelName);
std::string ERR_USERONCHANNEL(const std::string &nickname, const std::string &channelName);
std::string	ERR_NICKNAMEINUSE(const std::string &nickname);
std::string	ERR_NOORIGIN(void);
std::string ERR_NORECIPIENT(const std::string &cmdName);
std::string ERR_CANNOTSENDTOCHAN(const std::string &channelName);
std::string ERR_UNKNOWNMODE(const char &c, const Channel &channel);
std::string ERR_UMODEUNKNOWNFLAG(const char &flag);
std::string ERR_UMODEUNKNOWNFLAG(const std::string &mode);
std::string	ERR_USERSDONTMATCH(void);
std::string ERR_CHANOPRIVSNEEDED(const std::string &channelName);
std::string ERR_UNKNOWNCOMMAND(std::string &cmd);
std::string ERR_KEYSET(const Channel &channel);
std::string ERR_CHANNELISFULL(const Channel &channel);
std::string ERR_INVITEONLYCHAN(const Channel &channel);
std::string ERR_BANNEDFROMCHAN(const Channel &channel);
std::string ERR_BADCHANNELKEY(const Channel &channel);
std::string ERR_USERNOTINCHANNEL(const std::string &nickname, const Channel &channel);
std::string ERR_CHANOPRIVSNEEDED(const Channel &channel);
std::string ERR_NICKCOLLISION(const std::string &nickname);
std::string ERR_NOPRIVILEGES(void);

#endif
