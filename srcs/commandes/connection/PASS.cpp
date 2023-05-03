/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:31:04 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/11/21 13:19:55 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

void	PASS(User &user, Server &server, std::string &cmd)
{
	(void)server;
	std::vector<std::string> split = splitString(cmd, " ");
	
	if (split.size() < 2)
	{
		user.sendCmd(ERR_NEEDMOREPARAMS(split[0]));
		return;
	}
	else if (user.getRegisterStatus())
	{
		user.sendCmd(ERR_ALREADYREGISTRED());
		return;
	}
	
	int index = split[0].length() + 1;
	while (cmd[index] == ' ')
	{
		index++;
	}
	std::string password = cmd.substr(index, cmd.length());
	
	user.setPassword(password);
}
