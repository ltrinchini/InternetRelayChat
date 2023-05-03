/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:12:58 by ljourand          #+#    #+#             */
/*   Updated: 2022/11/21 13:32:48 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

void MODE(User &user, Server &server, std::string &cmd)
{
	std::vector<std::string> split = splitString(cmd);

	if (split.size() < 2)
	{
		user.sendCmd(ERR_NEEDMOREPARAMS(cmd));
		return;
	}
	
	std::string &target = split[1];


	if (checkChannelName(target))
	{
		if (!server.checkIfChannelExist(target))
		{
			user.sendCmd(ERR_NOSUCHCHANNEL(target));
			return;
		}
		
		Channel &channel = server.findChannel(target);
		if (!channel.checkUserIn(user))
		{
			user.sendCmd(ERR_NOTONCHANNEL(target));
			return;
		}
		
		if (split.size() < 3)
		{
			user.sendCmd(RPL_CHANNELMODEIS(channel));
			return;
		}

		if (!channel.isOper(user))
		{
			user.sendCmd(ERR_CHANOPRIVSNEEDED(channel));
			return;
		}

		std::string &flags = split[2];

		if (flags == "I")
		{
			const std::vector<const User *> &listInvites = channel.getListInvites();
			for (size_t i = 0; i < listInvites.size(); i++)
			{
				user.sendCmd(RPL_INVITELIST(channel, listInvites[i]->getNickname()));
			}
			user.sendCmd(RPL_ENDOFINVITELIST(channel));
			return;
		}
		
		bool status = (flags[0] == '+');
		size_t indexArg = 3;
		for (size_t i = 1; i < flags.length(); i++)
		{
			std::string response = user.getPrefix() + " MODE " + channel.getName() + " ";
			response.push_back(flags[0]);
			response.push_back(flags[i]);
			
			switch (flags[i])
			{
				case 'o':
					if (split.size() < indexArg)
					{
						user.sendCmd(ERR_NEEDMOREPARAMS(cmd));
						continue;
					}
					else
					{
						if (!channel.setOperator(split[indexArg], status))
						{
							user.sendCmd(ERR_USERNOTINCHANNEL(split[indexArg], channel));
							indexArg++;
							continue;
						}
						response += " ";
						response += split[indexArg];
						indexArg++;
					}
					break;
				case 'p':
					channel.setPrivate(status);
					break;
				case 's':
					channel.setSecret(status);
					break;
				case 'i':
					channel.setInviteOnly(status);
					break;
				case 't':
					channel.setTopicSettableOper(status);
					break;
				case 'n':
					channel.setOutsideMsgAllowed(status);
					break;
				case 'm':
					channel.setModerated(status);
					break;
				case 'l':
					if (status)
					{
						if (split.size() < indexArg)
						{
							user.sendCmd(ERR_NEEDMOREPARAMS(cmd));
							continue;
						}
						else
						{
							channel.setUserLimit(std::atoi(split[indexArg].c_str()));
							response += " ";
							response += split[indexArg];
							indexArg++;
						}
					}
					else
					{
						channel.setUserLimit(-1);
					}
					break;
				case 'b':
					if (split.size() < indexArg)
					{
						const std::vector<std::string> &listBan = channel.getListBanMask();
						for (size_t i = 0; i < listBan.size(); i++)
						{
							user.sendCmd(RPL_BANLIST(channel, listBan[i]));
						}
						user.sendCmd(RPL_ENDOFBANLIST(channel));
						continue;
					}
					else
					{
						channel.setBanMask(split[indexArg], status);
						response += " ";
						response += split[indexArg];
						indexArg++;
					}
					break;
				case 'v':
					if (split.size() < indexArg)
					{
						user.sendCmd(ERR_NEEDMOREPARAMS(cmd));
						continue;
					}
					else
					{
						if (!channel.setChatter(split[indexArg], status))
						{
							user.sendCmd(ERR_USERNOTINCHANNEL(split[indexArg], channel));
							indexArg++;
							continue;
						}
						response += " ";
						response += split[indexArg];
						indexArg++;
					}
					break;
				case 'k':
					if (split.size() < indexArg)
					{
						user.sendCmd(ERR_NEEDMOREPARAMS(cmd));
						continue;
					}
					else
					{
						if (channel.getKey() != "" && status)
						{
							user.sendCmd(ERR_KEYSET(channel));
							indexArg++;
							continue;
						}
						else
						{
							channel.setKey(split[indexArg], status);
						}
						response += " ";
						response += split[indexArg];
						indexArg++;
					}
					break;
				default:
					user.sendCmd(ERR_UNKNOWNMODE(flags[i], channel));
					continue;
			}
			channel.sendCmd(response);
		}
	}
	else
	{
		if (target != user.getNickname())
		{
			user.sendCmd(ERR_USERSDONTMATCH());
			return;
		}

		if (split.size() < 3)
		{
			user.sendCmd(RPL_UMODEIS(user));
			return;
		}
		
		std::string &flags = split[2];

		bool status = (flags[0] == '+');
		for (size_t i = 1; i < flags.length(); i++)
		{
			switch (flags[i])
			{
				case 'i':
					user.setInvisible(status);
					break;
				case 'o':
					if (status)
					{
						continue;
					}
					user.setOper(status);
					break;
				case 'w':
					user.setWallops(status);
					break;
				case 's':
					user.setNoticeReceiver(status);
					break;
				case 'a':
					user.setAway(status);
					break;
				default:
					user.sendCmd(ERR_UMODEUNKNOWNFLAG(flags[i]));
					continue;
			}
			std::string response = user.getPrefix() + " MODE " + user.getNickname() + " ";
			response.push_back(flags[0]);
			response.push_back(flags[i]);
			user.sendCmd(response);
		}
	}
}
