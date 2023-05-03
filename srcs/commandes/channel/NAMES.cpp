/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NAMES.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:36:01 by ljourand          #+#    #+#             */
/*   Updated: 2022/11/21 13:19:22 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

static void printAllInfo(User &user, Server &server)
{
	std::vector<User> userPrint;
	std::vector<const User *> listMembers;
	for (Server::iterator_channel channelIt = server.getListChannels().begin(); channelIt != server.getListChannels().end(); channelIt++)
	{
		if (!(*channelIt).isSecret())
		{
			user.sendCmd(RPL_NAMREPLY((*channelIt), user));
			user.sendCmd(RPL_ENDOFNAMES((*channelIt), user));

			listMembers = (*channelIt).getListMembers();
			for (std::vector<const User *>::iterator userIt = listMembers.begin(); userIt != listMembers.end(); userIt++)
			{
				userPrint.push_back(*(*userIt));
			}
		}
	}

	std::string userWithoutChannel;
	for (std::list<User>::const_iterator userIt = server.getListUsers().begin(); userIt != server.getListUsers().end(); userIt++)
	{
		if (std::find(userPrint.begin(), userPrint.end(), (*userIt)) == userPrint.end())
		{
			if (!(*userIt).isInvisible())
			{
				userWithoutChannel += (*userIt).getNickname() + " ";
			}
		}
	}
	if (!userWithoutChannel.empty())
	{
		user.sendCmd(RPL_NAMREPLY(user, userWithoutChannel));
		user.sendCmd(RPL_ENDOFNAMES(user));
	}
}

void NAMES(User &user, Server &server, std::string &cmd)
{
	std::vector<std::string> split = splitString(cmd);

	if (split.size() < 2)
	{
		printAllInfo(user, server);
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
				if (!channel.isSecret())
				{
					user.sendCmd(RPL_NAMREPLY(channel, user));
				}
				user.sendCmd(RPL_ENDOFNAMES(channel, user));
			}
			else
			{
				user.sendCmd(RPL_ENDOFNAMES(user, split[1]));
			}
		}
	}
}
