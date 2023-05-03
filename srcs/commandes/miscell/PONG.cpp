/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PONG.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:35:33 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/11/17 17:14:58 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

void PONG(User &user, Server &server, std::string &cmd)
{
	std::vector<std::string> split = splitString(cmd, " ");

	if (split.size() == 1)
	{
		user.sendCmd(ERR_NOORIGIN());
		return;
	}
	else if (!server.checkPassword(user.getPassword()))
	{
		user.sendCmd(ERR_PASSWDMISMATCH(user.getPassword()));
		server.disconnectUser(user);
		return;
	}
	
	std::string &message = split[1];
	if (!user.checkPingMsg(message))
	{
		user.sendCmd(ERR_INCORRECTEPINGREPLY());
		return;
	}
	
	if (!user.getRegisterStatus())
	{
		server.connectUser(user);
	}
	user.setLastPing(message);
	user.setTimeLastPing();
	user.setTimeLastPong();
}
