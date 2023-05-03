/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER_CMD.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:34:39 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/11/21 13:20:01 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

void	USER(User &user, Server &server, std::string &cmd)
{
	std::vector<std::string> split = splitString(cmd, " ");
	
	if (split.size() < 5)
	{
		user.sendCmd(ERR_NEEDMOREPARAMS(split[0]));
		return;
	}
	else if (user.getRegisterStatus())
	{
		user.sendCmd(ERR_ALREADYREGISTRED());
		return;
	}
	std::string &username = split[1];
	
	int mode = atoi(split[2].c_str());
	if (mode < 0 || mode >= 32)
	{
		user.sendCmd(ERR_UMODEUNKNOWNFLAG(split[2]));
	}
	else
	{
		user.setInvisible(mode & INVISIBLE);
		user.setOper(mode & OPERATOR);
		user.setWallops(mode & WALLOPS);
		user.setNoticeReceiver(mode & NOTICERECEIVER);
		user.setAway(mode & AWAY);
	}

	std::string &realname = split[4];
	
	user.setUsername(username);
	user.setRealname(realname);
	
	if (user.canRegister())
	{
		server.ping(user, randomStr(10));
	}
}
