/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:01:20 by ljourand          #+#    #+#             */
/*   Updated: 2022/11/21 13:18:43 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

void	INVITE(User &user, Server &server, std::string &cmd)
{
	std::vector<std::string> split = splitString(cmd, " ");
	
	if (split.size() < 3)
	{
		user.sendCmd(ERR_NEEDMOREPARAMS(cmd));
		return;
	}

	std::string &nickname = split[1];
	std::list<User>::const_iterator userIt = server.findUserIt(nickname);
	if (userIt == server.getListUsers().end())
	{
		user.sendCmd(ERR_NOSUCHNICK(nickname));
		return;
	}
	
	std::string &channelName = split[2];
	if (server.checkIfChannelExist(channelName))
	{
		Channel &channel = server.findChannel(channelName);
		if (!channel.checkUserIn(user))
		{
			user.sendCmd(ERR_NOTONCHANNEL(channelName));
			return;
		}
		if (channel.checkUserIn(*userIt))
		{
			user.sendCmd(ERR_USERONCHANNEL(nickname, channelName));
			return;
		}
		if (!channel.isOper(user))
		{
			user.sendCmd(ERR_CHANOPRIVSNEEDED(channelName));
			return;
		}
		
		channel.invite(*userIt);
		userIt->sendCmd(user.getPrefix() + " " + cmd);
		user.sendCmd(RPL_INVITING(channelName, nickname));
	}
}
