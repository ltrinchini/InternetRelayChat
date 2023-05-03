 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responses.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:47:25 by ljourand          #+#    #+#             */
/*   Updated: 2022/11/17 17:28:58 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

std::string RPL_WELCOME(const User &user)
{
	return (user.getPrefix() + " 001 " + user.getNickname() + " :Welcome to the Internet Relay Network " + user.getPrefix());
}

std::string RPL_YOURHOST(const Server &server)
{
	return ("002 Your host is " + server.getName() + ", running version 1.0");
}

std::string RPL_CREATED(void)
{
	return ("003 This server was created 2022/11/11");
}

std::string RPL_MYINFO(const Server &server)
{
	return ("004 " + server.getName() + " 1.0 iswoa opsitnmlbvk" );
}

std::string	RPL_LUSERCLIENT(const Server &server)
{
	size_t nbInvisible = 0;
	for (std::list<User>::const_iterator userIt = server.getListUsers().begin(); userIt != server.getListUsers().end(); userIt++)
	{
		if ((*userIt).isInvisible())
		{
			nbInvisible++;
		}
	}
	return ("251 :There are " + toString(server.getListUsers().size()) + " users and " + toString(nbInvisible) + " invisible on 1 servers");
}

std::string RPL_LUSEROP(const Server &server)
{
	size_t nbOperators = 0;
	for (std::list<User>::const_iterator userIt = server.getListUsers().begin(); userIt != server.getListUsers().end(); userIt++)
	{
		if ((*userIt).isOper())
		{
			nbOperators++;
		}
	}
	if (nbOperators > 0)
	{
		return ("252 " + toString(nbOperators) + " :operator(s) online");
	}
	return ("");
}

std::string	RPL_LUSERCHANNELS(const Server &server)
{
	if (server.getListChannels().size() > 0)
	{
		return ("254 " + toString(server.getListChannels().size()) + " :channels formed");
	}
	else
	{
		return ("");
	}
}

std::string RPL_LUSERME(const Server &server)
{
	return ("255 :I have " + toString(server.getListUsers().size()) + " clients and 0 servers");
}

std::string RPL_MOTDSTART(const Server &server)
{
	return ("375 :- " + server.getName() + " Message of the day - ");
}

std::string RPL_MOTD(const std::string &line)
{
	return ("372 :- " + line);
}

std::string RPL_ENDOFMOTD(void)
{
	return ("376 :End of /MOTD command");
}

std::string RPL_NOTOPIC(Channel &channel, User &user)
{
	return ("331 " + user.getNickname() + " " + channel.getName() + " :No topic is set");
}

std::string RPL_TOPIC(Channel &channel, User &user)
{
	std::string topic = channel.getTopic();
	if (topic.empty())
	{
		return (RPL_NOTOPIC(channel, user));
	}
	return ("332 " + user.getNickname() + " " + channel.getName() + " :"+ channel.getTopic() +"");
}

std::string RPL_NAMREPLY(Channel &channel, User &user)
{
	std::string nicknames;

	const std::vector<const User *> &listUser = channel.getListMembers();

	for (size_t i = 0; i < listUser.size(); i++)
	{
		if (!listUser[i]->isInvisible())
		{
			if (channel.isOper(*listUser[i]))
			{
				nicknames += "@";
			}
			else if (channel.isAllowedChatter(*listUser[i]))
			{
				nicknames += "+";
			}
			nicknames += listUser[i]->getNickname() + " ";
		}
	}

	std::string type;
	
	if (channel.isSecret())
	{
		type = " @ ";
	}
	else if (channel.isPrivate())
	{
		type = " * ";
	}
	else
	{
		type = " = ";
	}
	return ("353 " + user.getNickname() + type + channel.getName() + " :" + nicknames);
}

std::string RPL_NAMREPLY(User &user, const std::string &nicknames)
{
	return ("353 " + user.getNickname() + " :" + nicknames);
}

std::string RPL_ENDOFNAMES(Channel &channel, User &user)
{
	return ("366 " + user.getNickname() + " " + channel.getName() + " :End of /NAMES list");
}

std::string RPL_ENDOFNAMES(User &user, const std::string &names /* = "" */)
{
	return ("366 " + user.getNickname() + " " + names + " " + " :End of /NAMES list");
}

std::string ERR_NOTEXTTOSEND(void)
{
	return ("412 :No text to send");
}

std::string ERR_NONICKNAMEGIVEN(void)
{
	return ("431 :No nickname given");
}

std::string ERR_ERRONEUSNICKNAME(const std::string &nickname)
{
	return ("432 " + nickname + " :Erroneus nickname");
}

std::string ERR_NEEDMOREPARAMS(const std::string &cmdName)
{
	return ("461 " + cmdName + " :Not enough parameters");
}

std::string ERR_ALREADYREGISTRED(void)
{
	return ("462 :You may not reregister");
}

std::string ERR_NOTREGISTERED(void)
{
	return ("451 :You have not registered");
}

std::string ERR_PASSWDMISMATCH(const std::string &password)
{
	return ("464 " + password + " :Password incorrect");
}

std::string ERR_ERR_NICKNAMEINUSE(const std::string &nickname)
{
	return ("433 " + nickname + " :Nickname is already in use");
}

std::string ERR_NOSUCHNICK(const std::string &nickname)
{
	return ("401 " + nickname + " :No such nick/channel");
}

std::string ERR_PINGTIMEOUT(void)
{
	return ("600 :Ping time out [close link]");
}

std::string ERR_INCORRECTEPINGREPLY(void)
{
	return ("601 :Incorrect ping reply for registration [close link]");
}

std::string ERR_BADCHANMASK(const std::string &nickClient, const std::string &channelName)
{
	return ("476 " + nickClient + " " + channelName + " :Bad Channel Mask");
}

std::string ERR_NOTONCHANNEL(const std::string &channelName)
{
	return ("442 " + channelName + " :You're not on that channel");
}

std::string ERR_NOSUCHCHANNEL(const std::string &channelName)
{
	return ("403 " + channelName + " :No such channel");
}

std::string ERR_USERONCHANNEL(const std::string &nickname, const std::string &channelName)
{
	return ("443 " + nickname + " " + channelName + " :is already on channel");
}

std::string	ERR_NICKNAMEINUSE(const std::string &nickname)
{
	return  ("443 " + nickname + " :Nickname is already in use");
}

std::string	ERR_NOORIGIN(void)
{
	return ("409 :No origin specified");
}

std::string ERR_NORECIPIENT(const std::string &cmdName)
{
	return ("411 :No recipient given " + cmdName);
}

std::string ERR_CANNOTSENDTOCHAN(const std::string &channelName)
{
	return ("404 " + channelName + " :Cannot send to channel");
}

std::string ERR_UNKNOWNMODE(const char &c, const Channel &channel)
{
	std::string str = "472 ";
	str.push_back(c);
	return (str + " :is unknown mode char to me for " + channel.getName());
}

std::string ERR_UMODEUNKNOWNFLAG(const char &flag)
{
	std::string tmp;
	tmp.push_back(flag);
	return ("501 " + tmp + ":Unknown MODE flag");
}

std::string ERR_UMODEUNKNOWNFLAG(const std::string &mode)
{
	return ("501 " + mode + " :Unknown MODE flag");
}

std::string	ERR_USERSDONTMATCH(void)
{
	return ("502 :Cant change mode for other users");
}

std::string	RPL_YOUREOPER(void)
{
	return ("381 :You are now an IRC operator");
}

std::string RPL_LIST(const Channel &channel, User &user)
{
	return ("322 " + user.getNickname() + " " + channel.getName() + " " + toString(channel.getListMembers().size()) + " :" + channel.getTopic());
}

std::string RPL_LIST_PRIV(const Channel &channel, User &user)
{
	return ("322 " + user.getNickname() + " * " + toString(channel.getListMembers().size()) + " :");
}

std::string RPL_LISTEND(User &user)
{
	return ("323 " + user.getNickname() + " :End of LIST");
}

std::string RPL_INVITING(const std::string &channelName, const std::string &nickname)
{
	return ("341 " + channelName + " " + nickname);
}

std::string ERR_CHANOPRIVSNEEDED(const std::string &channelName)
{
	return ("482 " + channelName + " :You're not channel operator");
}


std::string ERR_UNKNOWNCOMMAND(std::string &cmd)
{
	return ("421 " + cmd + ":Unknown command" );
}

std::string ERR_KEYSET(const Channel &channel)
{
	return ("467 " + channel.getName() + " :Channel key already set");
}

std::string ERR_CHANNELISFULL(const Channel &channel)
{
	return ("471 " + channel.getName() + " :Cannot join channel (+l)");
}

std::string ERR_INVITEONLYCHAN(const Channel &channel)
{
	return ("473 " + channel.getName() + " :Cannot join channel (+i)");
}

std::string ERR_BANNEDFROMCHAN(const Channel &channel)
{
	return ("474 " + channel.getName() + " :Cannot join channel (+b)");
}

std::string ERR_BADCHANNELKEY(const Channel &channel)
{
	return ("475 " + channel.getName() + " :Cannot join channel (+k)");
}

std::string ERR_USERNOTINCHANNEL(const std::string &nickname, const Channel &channel)
{
	return ("441 " + nickname + " " + channel.getName() + " :They aren't on that channel");
}

std::string ERR_CHANOPRIVSNEEDED(const Channel &channel)
{
	return ("482 " + channel.getName() + " :You're not channel operator");
}

std::string ERR_NICKCOLLISION(const std::string &nickname)
{
	return ("436 " + nickname + " :Nickname collision KILL");
}

std::string ERR_NOPRIVILEGES(void)
{
	return ("481 :Permission Denied- You're not an IRC operator");
}

std::string RPL_UMODEIS(const User &user)
{
	std::string flags = "+";
	if (user.isInvisible())
	{
		flags.push_back('i');
	}
	if (user.isOper())
	{
		flags.push_back('o');
	}
	if (user.isWallops())
	{
		flags.push_back('w');
	}
	if (user.isNoticeReceiver())
	{
		flags.push_back('s');
	}
	if (user.isAway())
	{
		flags.push_back('a');
	}
	return ("221 " + user.getNickname() + " :" + flags);
}

std::string RPL_CHANNELMODEIS(const Channel &channel)
{
	std::string flags = "+";
	std::string args = "";

	if (channel.isPrivate())
	{
		flags.push_back('p');
	}
	if (channel.isSecret())
	{
		flags.push_back('s');
	}
	if (channel.isInviteOnly())
	{
		flags.push_back('i');
	}
	if (channel.isTopicSettableOper())
	{
		flags.push_back('t');
	}
	if (channel.isOutsideMsgAllowed())
	{
		flags.push_back('n');
	}
	if (channel.isModerated())
	{
		flags.push_back('m');
	}
	if (channel.getUserLimit() != -1)
	{
		flags.push_back('l');
		args += " " + toString(channel.getUserLimit());
	}
	return ("324 " + channel.getName() + " :" + flags + args);
}

std::string RPL_BANLIST(const Channel &channel, const std::string &banMask)
{
	return ("367 " + channel.getName() + " " + banMask);
}

std::string RPL_ENDOFBANLIST(const Channel &channel)
{
	return ("368 " + channel.getName() + " :End of channel ban list");
}

std::string RPL_INVITELIST(const Channel &channel, const std::string &inviteMask)
{
	return ("346 " + channel.getName() + " " + inviteMask);
}

std::string RPL_ENDOFINVITELIST(const Channel &channel)
{
	return ("347 " + channel.getName() + " :End of channel invite list");
}
