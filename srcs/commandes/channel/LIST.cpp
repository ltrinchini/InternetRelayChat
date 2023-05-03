/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:11:49 by ljourand          #+#    #+#             */
/*   Updated: 2022/11/21 13:16:53 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

void LIST(User &user, Server &server, std::string &cmd)
{
	std::vector<std::string> split = splitString(cmd);

	if (split.size() < 2)
	{
		const std::vector<Channel> &listChannel = server.getListChannels();

		for (size_t i = 0; i < listChannel.size(); i++)
		{
			if (!listChannel[i].isSecret())
			{
				if (listChannel[i].isPrivate())
				{
					user.sendCmd(RPL_LIST_PRIV(listChannel[i], user));
				}
				else
				{
					user.sendCmd(RPL_LIST(listChannel[i], user));
				}
			}
		}
		user.sendCmd(RPL_LISTEND(user));
	}
	else
	{
		std::string &listChannelStr = split[1];
		std::vector<std::string> listChannel = splitString(listChannelStr, ",");

		for (size_t i = 0; i < listChannel.size(); i++)
		{
			if (server.checkIfChannelExist(listChannel[i]))
			{
				Channel &channel = server.findChannel(listChannel[i]);
				if (channel.isPrivate())
				{
					user.sendCmd(RPL_LIST_PRIV(channel, user));
				}
				else
				{
					user.sendCmd(RPL_LIST(channel, user));
				}
			}
		}
		user.sendCmd(RPL_LISTEND(user));
	}
}
