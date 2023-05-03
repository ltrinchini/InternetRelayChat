/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:49:42 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/11/21 17:09:19 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

void TOPIC(User &user, Server &server, std::string &cmd)
{
	std::vector<std::string> split = splitString(cmd);

	if (split.size() < 2)
	{
		user.sendCmd(ERR_NEEDMOREPARAMS(split[0]));
		return;
	}

	std::string &channelName = split[1];
	if (!server.checkIfChannelExist(channelName))
	{
		user.sendCmd(ERR_NOSUCHCHANNEL(channelName));
		return;
	}

	Channel &channel = server.findChannel(channelName);
	if (!channel.checkUserIn(user))
	{
		user.sendCmd(ERR_NOTONCHANNEL(channelName));
		return;
	}
	
	if (split.size() == 2)
	{
		user.sendCmd(RPL_TOPIC(channel, user));
		return;
	}

	if (channel.isTopicSettableOper() && !channel.isOper(user))
	{
		user.sendCmd(ERR_CHANOPRIVSNEEDED(channel));
		return;
	}

	std::string topic;
	size_t index = cmd.find(':', 0);
	if (index == std::string::npos)
	{
		topic = split[2];
	}
	else
	{
		topic = cmd.substr(index, cmd.length());
	}

	channel.setTopic(topic);
	channel.sendCmd(user.getPrefix() + " TOPIC " + channel.getName() + " :" + channel.getTopic());
}
