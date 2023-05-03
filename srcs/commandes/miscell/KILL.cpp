/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KILL.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:03:52 by ljourand          #+#    #+#             */
/*   Updated: 2022/11/21 13:20:09 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/irc.hpp"

void	KILL(User &user, Server &server, std::string &cmd)
{
	if (!user.isOper())
	{
		user.sendCmd(ERR_NOPRIVILEGES());
		return;
	}
	
	std::vector<std::string> split = splitString(cmd);
	
	if (split.size() < 3)
	{
		user.sendCmd(ERR_NEEDMOREPARAMS(cmd));
		return;
	}

	std::string &nickname = split[1];

	std::list<User>::const_iterator it = server.findUserIt(nickname);
	if (it == server.getListUsers().end())
	{
		user.sendCmd(ERR_NOSUCHNICK(nickname));
		return;
	}
	
	std::string comment;
	size_t index = cmd.find(':', 0);
	if (index == std::string::npos)
	{
		comment = split[2];
	}
	else
	{
		comment = cmd.substr(index, cmd.length());
	}
	if (comment[0] != ':')
	{
		comment = ":" + comment;
	}
	
	it->sendCmd(user.getPrefix() + " KILL " + nickname + " " + comment);
	server.disconnectUser(*it, comment);
}
