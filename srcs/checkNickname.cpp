/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkNickname.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:08:09 by ljourand          #+#    #+#             */
/*   Updated: 2022/11/17 13:55:16 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

static bool	checkChar(char c)
{
	if (std::isalnum(c))
	{
		return (true);
	}
	switch (c)
	{
		case '-':
			return (true);
		case '_':
			return (true);
		case '[':
			return (true);
		case ']':
			return (true);
		case '{':
			return (true);
		case '}':
			return (true);
		case '\\':
			return (true);
		case '`':
			return (true);
		case '|':
			return (true);
		default:
			return (false);
	}
}

bool	checkNickname(const std::string &nickname)
{
	if (nickname.length() > 9)
	{
		return (false);
	}
	for (size_t i = 0; i < nickname.length(); i++)
	{
		if (!checkChar(nickname[i]))
		{
			return (false);
		}
	}
	return (true);
}
