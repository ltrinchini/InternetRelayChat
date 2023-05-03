/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:16:36 by ljourand          #+#    #+#             */
/*   Updated: 2022/11/11 16:10:15 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <string>

std::vector<std::string> splitString(std::string str, std::string delimiter = " ")
{
	std::vector<std::string> split;
	std::string tmp;
	int start = 0;
	int end = str.find(delimiter);

	while (end != -1)
	{
		tmp = str.substr(start, end - start);
		if (!tmp.empty())
			split.push_back(tmp);
		start = end + delimiter.size();
		end = str.find(delimiter, start);
	}
	if (!str.substr(start, end - start).empty())
		split.push_back(str.substr(start, end - start));
	return (split);
}


std::vector<std::string> SplitStringKeep(std::string str, std::string delimiter = " ")
{
	std::vector<std::string> rtn;
	std::string tmp;
	size_t start = 0;
	size_t end = str.find(delimiter);

	if (delimiter.empty())
		end = std::string::npos;

	while (end != std::string::npos)
	{
		tmp = str.substr(start, end - start);
		if (!tmp.empty())
			rtn.push_back(tmp);
		tmp.erase();
		start = end;
		while (str.compare(start, delimiter.size(), delimiter) == 0)
		{
			start += delimiter.size();
			tmp += delimiter;
		}
		if (!tmp.empty())
			rtn.push_back(tmp);
		end = str.find(delimiter, start);
	}
	if (!str.substr(start, end - start).empty())
		rtn.push_back(str.substr(start, end - start));
	return (rtn);
}
