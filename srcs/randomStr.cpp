/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomStr.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:35:19 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/11/09 16:47:15 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

std::string	randomStr(size_t length)
{
	static const std::string	charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	std::string			rtn;

	for (size_t i = 0; i < length; i++)
	{
		rtn += charset.at(rand() % charset.size());
	}
	return (rtn);
}
