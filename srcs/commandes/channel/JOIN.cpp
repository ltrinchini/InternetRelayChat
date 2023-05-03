/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:48:44 by ljourand          #+#    #+#             */
/*   Updated: 2022/11/21 13:21:09 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

void	JOIN(User &user, Server &server, std::string &cmd)
{
	std::vector<std::string> split = splitString(cmd, " ");
	
	if (split.size() < 2)
	{
		user.sendCmd(ERR_NEEDMOREPARAMS(split[0]));
		return;
	}

	if (split.size() == 2)
	{
		if (split[1] == "0")
		{
			for (Server::iterator_channel channelIt = server.getListChannels().begin(); channelIt < server.getListChannels().end(); channelIt++)
			{
				channelIt->delUser(user);
			}
			return ;
		}
	}

	std::string	listChannelsStr = split[1];
	std::string	listKeysStr;
	if (split.size() > 2)
	{
		listKeysStr = split[2];
	}
	
	std::vector<std::string> listChannels = splitString(listChannelsStr, ",");
	std::vector<std::string> listKeys = splitString(listKeysStr, ",");
	
	for (size_t i = 0; i < listChannels.size(); i++)
	{
		if (!checkChannelName(listChannels[i]))
		{
			user.sendCmd(ERR_BADCHANMASK(user.getNickname(), listChannels[i]));
			continue ;
		}
		bool isOper = false;
		if (!server.checkIfChannelExist(listChannels[i]))
		{
			isOper = true;
			std::cout << "created channel" << std::endl;
		}
		Channel &channel = server.findChannel(listChannels[i]);

		if (channel.checkUserIn(user)) 
		{
			continue;
		}

		if (channel.isBanned(user))
		{
			user.sendCmd(ERR_BANNEDFROMCHAN(channel));
			continue;
		}

		if (channel.isInviteOnly() && !channel.isInvited(user))
		{
			user.sendCmd(ERR_INVITEONLYCHAN(channel));
			continue;
		}

		const std::vector<const User *> &listMembers = channel.getListMembers();
		if (channel.getUserLimit() != -1 && channel.getUserLimit() <= (int)listMembers.size())
		{
			user.sendCmd(ERR_CHANNELISFULL(channel));
			continue;
		}
		
		if (i < listKeys.size())
		{
			if (!channel.checkKey(listKeys[i]))
			{
				user.sendCmd(ERR_BADCHANNELKEY(channel));
				continue;
			}
		}
		else if (!channel.checkKey(""))
		{
			user.sendCmd(ERR_BADCHANNELKEY(channel));
			continue;
		}

		channel.addUser(user);
		if (isOper)
		{
			channel.setOperator(user.getNickname(), true);
		}

		channel.sendCmd(user.getPrefix() + " JOIN :" + channel.getName());
		user.sendCmd(RPL_TOPIC(channel, user));
		user.sendCmd(RPL_NAMREPLY(channel, user));
		user.sendCmd(RPL_ENDOFNAMES(channel, user));
	}
}
