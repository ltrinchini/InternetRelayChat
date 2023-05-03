/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:48:13 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/11/18 16:10:27 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/irc.hpp"

void	QUIT(User &user, Server &server, std::string &cmd)
{
	std::vector<std::string> split = splitString(cmd);
	
	std::string message = QUIT_DFL_MSG;

	if (split.size() > 1)
	{
		size_t index = cmd.find(':', 0);
		if (index == std::string::npos)
		{
			message = split[1];
		}
		else
		{
			message = cmd.substr(index, cmd.length());
		}
	}
	if (message[0] != ':')
	{
		message = ":" + message;
	}

	user.sendCmd("ERROR :Closing link: (" + user.getUsername() + "@" + user.getAddressIP() + ") [" + message + "]");
	server.disconnectUser(user, message);
}
