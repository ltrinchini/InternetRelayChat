/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:10:43 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/11/21 11:32:36 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

static size_t skipFind(const std::string &string, size_t start, const std::string &mask, std::string delimiter)
{
	std::vector<std::string> split_mask = SplitStringKeep(mask, delimiter);
	size_t pos = start;
	size_t rtn = 0;

	for (std::vector<std::string>::iterator maskIt = split_mask.begin(); maskIt < split_mask.end(); maskIt++)
	{
		if ((*maskIt).find(delimiter) == std::string::npos)
		{
			rtn = string.find(*maskIt, pos);
			if (rtn == std::string::npos)
				return (rtn);
		}
		pos += (*maskIt).size();
	}
	if (pos > string.size())
		return (std::string::npos);
	return (pos - mask.size());
}

static size_t skipRFind(const std::string &string, size_t start, const std::string &mask, std::string delimiter)
{
	std::vector<std::string> split_mask = SplitStringKeep(mask, delimiter);
	size_t pos = start;
	size_t rtn = 0;

	for (std::vector<std::string>::iterator maskIt = split_mask.begin(); maskIt < split_mask.end(); maskIt++)
	{
		if ((*maskIt).find(delimiter) == std::string::npos)
		{
			rtn = string.rfind(*maskIt, string.length());
			if (rtn == std::string::npos)
			{
				return (rtn);
			}
			pos = rtn + (*maskIt).size();
		}
		else
		{
			if (pos + (*maskIt).length() > string.length())
				return (std::string::npos);
			return (string.length() - (*maskIt).length());
		}
	}
	if (pos > string.size())
		return (std::string::npos);
	return (pos - mask.length());
}

bool checkMask(const std::string &string, const std::string &mask)
{
	size_t pos = 0;
	size_t rtn = 0;
	bool begin_with = (*mask.begin()) != '*';
	bool end_with = (*(mask.end() - 1)) != '*';
	std::vector<std::string> maskSplit = splitString(mask);

	for (size_t i = 0; i < maskSplit.size(); i++)
	{
		if (begin_with && i == 0)
		{
			rtn = skipFind(string, pos, maskSplit[i], "?");
			if (rtn != 0)
			{
				return (false);
			}
		}
		else if (end_with && i == maskSplit.size() - 1)
		{
			rtn = skipRFind(string, pos, maskSplit[i], "?");
		}
		else
		{
			rtn = skipFind(string, pos, maskSplit[i], "?");
		}

		if (rtn == std::string::npos)
			return (false);

		pos = rtn + maskSplit[i].size();
		if (end_with && i == maskSplit.size() - 1)
		{
			if ((string.begin() + pos) != string.end())
			{
				return (false);
			}
		}
	}
	return (true);
}
