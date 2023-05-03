/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkChannelname.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:09:12 by ljourand          #+#    #+#             */
/*   Updated: 2022/11/10 15:15:11 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

bool checkChannelName(std::string &channelName)
{
	if (channelName.size() > SIZEMAX_CHANNEL_NAME)
	{
		return (false);
	}
	if (channelName.at(0) != '&' && channelName.at(0) != '#')
	{
		return (false);
	}
	if (channelName.find(CTRL_G) != std::string::npos)
	{
		return (false);
	}
	if (channelName.find(',') != std::string::npos)
	{
		return (false);
	}
	if (channelName.find(' ') != std::string::npos)
	{
		return (false);
	}
	return (true);
}
