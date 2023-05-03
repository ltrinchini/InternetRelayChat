/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:32:24 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/11/21 13:19:47 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

void	NICK(User &user, Server &server, std::string &cmd)
{
	std::vector<std::string> split = splitString(cmd, " ");
	
	if (split.size() < 2)
	{
		user.sendCmd(ERR_NONICKNAMEGIVEN());
		return;
	}
	
	std::string &nickname = split[1];
	if (!checkNickname(nickname))
	{
		user.sendCmd(ERR_ERRONEUSNICKNAME(nickname));
		return;
	}
	else if (server.checkNicknameInUse(nickname))
	{
		user.sendCmd(ERR_NICKNAMEINUSE(nickname));
		return;
	}
	if (user.getRegisterStatus())
	{
		user.sendCmd(user.getPrefix() + " NICK " + nickname);
	}
	user.setNickname(nickname);

	if (user.canRegister())
	{
		server.ping(user, randomStr(10));
	}
}
