/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:52:00 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/11/21 13:19:30 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

void PART (User &user, Server &server, std::string &cmd)
{
	std::vector<std::string> split = splitString(cmd);

	if (split.size() < 2)
	{
		user.sendCmd(ERR_NEEDMOREPARAMS(cmd));
	}
	std::string	listChannelsStr = split[1];
	std::vector<std::string> listChannels = splitString(listChannelsStr, ",");
	
	std::string	message = PART_DFL_MSG;
	if (split.size() >= 3)
	{
		size_t index = cmd.find(':', 0);
		if (index == std::string::npos)
		{
			message = split[2];
		}
		else
		{
			message = cmd.substr(index, cmd.length());
		}
	}
	if (message[0] != ':')
	{
		message = ":" + message;
	}
	
	for (size_t i = 0; i < listChannels.size(); i++)
	{
		if (!server.checkIfChannelExist(listChannels[i]))
		{
			user.sendCmd(ERR_NOSUCHCHANNEL(listChannels[i]));
			continue ;
		}

		Channel &channel = server.findChannel(listChannels[i]);
		if (!channel.checkUserIn(user))
		{
			user.sendCmd(ERR_NOTONCHANNEL(channel.getName()));
			continue;
		}
		channel.sendCmd(user.getPrefix() + " PART " + channel.getName() + " " + message);
		channel.delUser(user);
	}
}
