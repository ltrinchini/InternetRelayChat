/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:28:31 by ljourand          #+#    #+#             */
/*   Updated: 2022/11/21 13:21:14 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

void	KICK(User &user, Server &server, std::string &cmd)
{
	std::vector<std::string> split = splitString(cmd, " ");
	
	if (split.size() < 3)
	{
		user.sendCmd(ERR_NEEDMOREPARAMS(split[0]));
		return;
	}

	std::string	&listChannelsStr = split[1];
	std::string	&listUsersStr = split[2];

	std::string comment = KICK_DFL_MSG;

	if (split.size() > 3)
	{
		size_t index = cmd.find(':', 0);
		if (index == std::string::npos)
		{
			comment = split[2];
		}
		else
		{
			comment = cmd.substr(index, cmd.length());
		}
	}
	if (comment[0] != ':')
	{
		comment = ":" + comment;
	}
	
	std::vector<std::string> listChannels = splitString(listChannelsStr, ",");
	std::vector<std::string> listUsers = splitString(listUsersStr, ",");

	for (size_t i = 0; i < listChannels.size(); i++)
	{
		if (!server.checkIfChannelExist(listChannels[i]))
		{
			user.sendCmd(ERR_NOSUCHCHANNEL(listChannels[i]));
			continue;
		}
		
		Channel &channel = server.findChannel(listChannels[i]);
		
		if (!channel.checkUserIn(user))
		{
			user.sendCmd(ERR_NOTONCHANNEL(listChannels[i]));
			continue;
		}
		
		if (!channel.isOper(user))
		{
			user.sendCmd(ERR_CHANOPRIVSNEEDED(listChannels[i]));
			continue;
		}
		
		for (size_t i = 0; i < listUsers.size(); i++)
		{
			if (!channel.checkUserIn(listUsers[i]))
			{
				user.sendCmd(ERR_USERNOTINCHANNEL(listUsers[i], channel));
				continue;
			}

			channel.sendCmd(user.getPrefix() + " KICK " + channel.getName() + " " + listUsers[i] + " " + comment);
			channel.delUser(*server.findUserIt(listUsers[i]));
		}
	}
}
