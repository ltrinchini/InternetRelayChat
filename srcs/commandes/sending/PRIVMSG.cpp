/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:31:20 by ljourand          #+#    #+#             */
/*   Updated: 2022/11/21 13:20:19 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

void PRIVMSG(User &user, Server &server, std::string &cmd)
{
	std::vector<std::string> split = splitString(cmd, " ");

	if (split.size() < 2)
	{
		user.sendCmd(ERR_NORECIPIENT(split[0]));
		return;
	}
	else if (split.size() < 3)
	{
		user.sendCmd(ERR_NOTEXTTOSEND());
		return;
	}
	std::string target = split[1];
	
	std::string message;
	size_t index = cmd.find(':', 0);
	if (index == std::string::npos)
	{
		message = split[2];
	}
	else
	{
		message = cmd.substr(index, cmd.length());
	}
	if (message[0] != ':')
	{
		message = ":" + message;
	}

	if (target[0] == '#' || target[0] == '&')
	{
		std::transform(target.begin(), target.end(), target.begin(), tolower);
		std::vector<Channel *> listChannels = server.findChannelByMask(target);

		if (listChannels.size() == 0)
		{
			user.sendCmd(ERR_CANNOTSENDTOCHAN(target));
		}

		for (size_t i = 0; i < listChannels.size(); i++)
		{
			if (!listChannels[i]->isOutsideMsgAllowed() && !listChannels[i]->checkUserIn(user))
			{
				user.sendCmd(ERR_CANNOTSENDTOCHAN(listChannels[i]->getName()));
				continue;
			}

			if (listChannels[i]->getKey() != "" && !listChannels[i]->checkUserIn(user))
			{
				user.sendCmd(ERR_CANNOTSENDTOCHAN(listChannels[i]->getName()));
				continue;
			}

			if (listChannels[i]->isBanned(user))
			{
				user.sendCmd(ERR_CANNOTSENDTOCHAN(listChannels[i]->getName()));
				continue;
			}

			if (listChannels[i]->isModerated() && !listChannels[i]->isAllowedChatter(user) && !listChannels[i]->isOper(user))
			{
				user.sendCmd(ERR_CANNOTSENDTOCHAN(listChannels[i]->getName()));
				continue;
			}
			
			listChannels[i]->sendCmd(split[0] + " " + listChannels[i]->getName() + " " + message, user);
		}
	}
	else
	{
		std::vector<User *> listUsers = server.findUserByMask(target);

		if (listUsers.size() == 0)
		{
			user.sendCmd(ERR_NOSUCHNICK(target));
		}

		for (size_t i = 0; i < listUsers.size(); i++)
		{
			listUsers[i]->sendCmd(user.getPrefix() + " " + split[0] + " " + listUsers[i]->getNickname() + " " + message);
		}
	}
}
