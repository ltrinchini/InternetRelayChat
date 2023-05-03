/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OPER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:31:49 by ljourand          #+#    #+#             */
/*   Updated: 2022/11/21 13:19:51 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

void	OPER(User &user, Server &server, std::string &cmd)
{
	std::vector<std::string> split = splitString(cmd);

	if (split.size() < 3)
	{
		user.sendCmd(ERR_NEEDMOREPARAMS(split[0]));
		return;
	}
	
	std::string &target = split[1];
	if (target != user.getNickname())
	{
		return;
	}
	
	std::string &password = split[2];
	if (!server.checkPasswordOper(password))
	{
		user.sendCmd(ERR_PASSWDMISMATCH(password));
		return;
	}
	else
	{
		user.sendCmd(RPL_YOUREOPER());
		user.setOper(true);
	}
}
