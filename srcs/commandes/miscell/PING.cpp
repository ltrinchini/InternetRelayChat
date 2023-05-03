/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:07:02 by ljourand          #+#    #+#             */
/*   Updated: 2022/11/17 17:14:55 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

void	PING(User &user, Server &server, std::string &cmd)
{
	(void)server;
	std::vector<std::string> split = splitString(cmd, " ");
	
	if (split.size() < 2)
	{
		user.sendCmd(ERR_NOORIGIN());
		return;
	}
	user.sendCmd("PONG " + split[1]);
}
