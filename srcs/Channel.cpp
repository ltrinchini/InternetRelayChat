/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:00:28 by ljourand          #+#    #+#             */
/*   Updated: 2022/11/21 17:32:23 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(const std::string &name) : _channelName(name), _flags(0), _userLimit(-1)
{
}

Channel::~Channel(void)
{
}

const std::string &Channel::getName(void) const
{
	return (this->_channelName);
}

const std::string &Channel::getTopic(void) const
{
	return (this->_topic);
}

const std::vector<const User *> &Channel::getListMembers(void) const
{
	return (this->_listMembers);
}

const std::vector<std::string>	&Channel::getListBanMask(void) const
{
	return (this->_listBanMask);
}

const std::vector<const User *>		&Channel::getListInvites(void) const
{
	return (this->_listInvites);
}

const User	*Channel::_getUser(const std::string &nickname) const
{
	for (size_t i = 0; i < this->_listMembers.size(); i++)
	{
		if (this->_listMembers[i]->getNickname() == nickname)
		{
			return (this->_listMembers[i]);
		}
	}
	return (NULL);
}

void Channel::setTopic(const std::string &topic)
{
	std::string tmp_topic = topic;

	if (tmp_topic.at(0) == ':')
	{
		tmp_topic.erase(0, 1);
	}
	this->_topic = tmp_topic;
}

void Channel::addUser(const User &user)
{
	std::vector<const User *>::iterator it = std::find(this->_listInvites.begin(), this->_listInvites.end(), &user);
	if (it != this->_listInvites.end())
	{
		this->_listInvites.erase(it);
	}
	this->_listMembers.push_back(&user);
}

void Channel::delUser(const User &user)
{
	iterator it = std::find(this->_listMembers.begin(), this->_listMembers.end(), &user);
	if (it != this->_listMembers.end())
	{
		this->_listMembers.erase(it);
	}
	
	it = std::find(this->_listOperators.begin(), this->_listOperators.end(), &user);
	if (it != this->_listOperators.end())
	{
		this->_listOperators.erase(it);
	}
	
	if (this->_listOperators.size() == 0 && this->_listMembers.size() != 0)
	{
		this->setOperator(this->_listMembers[0]->getNickname(), true);
		this->sendCmd(user.getPrefix() + " MODE " + this->_channelName + " +o " + this->_listMembers[0]->getNickname());
	}
}

void Channel::sendCmd(const std::string &cmd)
{
	for (iterator it = this->_listMembers.begin(); it < this->_listMembers.end(); it++)
	{
		(*it)->sendCmd(cmd);
	}
}

void Channel::sendCmd(const std::string &cmd, const User &sender)
{
	std::string prefix = sender.getPrefix();
	for (iterator it = this->_listMembers.begin(); it < this->_listMembers.end(); it++)
	{
		if (*it != &sender)
		{
			(*it)->sendCmd(prefix + " " + cmd);
		}
	}
}

bool Channel::checkUserIn(const User &user)
{
	return (std::find(this->_listMembers.begin(), this->_listMembers.end(), &user) != this->_listMembers.end());
}

bool Channel::checkUserIn(const std::string &nickname)
{
	for (std::vector<const User *>::iterator it = this->_listMembers.begin(); it < this->_listMembers.end(); it++)
	{
		if ((*it)->getNickname() == nickname)
		{
			return (true);
		}
	}
	return (false);
}

// Flags
// getters
bool	Channel::isPrivate(void) const
{
	return ((this->_flags & PRIVATE) == PRIVATE);
}

bool	Channel::isSecret(void) const
{
	return ((this->_flags & SECRET) == SECRET);
}

bool	Channel::isInviteOnly(void) const
{
	return ((this->_flags & INVITEONLY) == INVITEONLY);
}

bool	Channel::isTopicSettableOper(void) const
{
	return ((this->_flags & TOPICSETTABLEOPER) == TOPICSETTABLEOPER);
}

bool	Channel::isOutsideMsgAllowed(void) const
{
	return ((this->_flags & OUTSIDEMSGALLOWED) == OUTSIDEMSGALLOWED);
}

bool	Channel::isModerated(void) const
{
	return ((this->_flags & MODERATED) == MODERATED);
}

// setters
void	Channel::setPrivate(bool status)
{
	if (status)
	{
		this->_flags |= PRIVATE;
	}
	else
	{
		this->_flags &= ~PRIVATE;
	}
}

void	Channel::setSecret(bool status)
{
	if (status)
	{
		this->_flags |= SECRET;
	}
	else
	{
		this->_flags &= ~SECRET;
	}
}

void	Channel::setInviteOnly(bool status)
{
	if (status)
	{
		this->_flags |= INVITEONLY;
	}
	else
	{
		this->_flags &= ~INVITEONLY;
	}
}

void	Channel::setTopicSettableOper(bool status)
{
	if (status)
	{
		this->_flags |= TOPICSETTABLEOPER;
	}
	else
	{
		this->_flags &= ~TOPICSETTABLEOPER;
	}
}

void	Channel::setOutsideMsgAllowed(bool status)
{
	if (status)
	{
		this->_flags |= OUTSIDEMSGALLOWED;
	}
	else
	{
		this->_flags &= ~OUTSIDEMSGALLOWED;
	}
}

void	Channel::setModerated(bool status)
{
	if (status)
	{
		this->_flags |= MODERATED;
	}
	else
	{
		this->_flags &= ~MODERATED;
	}
}

int		Channel::getUserLimit(void) const
{
	return (this->_userLimit);
}

void	Channel::setUserLimit(const int limit)
{
	this->_userLimit = limit;
}

void	Channel::setBanMask(const std::string &banMask, bool add)
{
	if (add)
	{
		this->_listBanMask.push_back(banMask);
	}
	else
	{
		for (std::vector<std::string>::iterator it = this->_listBanMask.begin(); it < this->_listBanMask.end(); it++)
		{
			if (*it == banMask)
			{
				this->_listBanMask.erase(it);
				break;
			}
		}
	}
}

const std::string	&Channel::getKey(void) const
{
	return (this->_key);
}

void	Channel::setKey(const std::string &key, bool add)
{
	if (add)
	{
		this->_key = key;
	}
	else
	{
		this->_key = "";
	}
}
bool	Channel::checkKey(const std::string &key)
{
	return (this->_key == key);
}

bool	Channel::setOperator(const std::string &nickname, bool add)
{
	if (add)
	{
		const User *user = this->_getUser(nickname);
		if (user)
		{
			this->_listOperators.push_back(user);
			return (true);
		}
	}
	else
	{
		for (std::vector<const User *>::iterator it = this->_listOperators.begin(); it < this->_listOperators.end(); it++)
		{
			if ((*it)->getNickname() == nickname)
			{
				this->_listOperators.erase(it);
				return (true);
			}
		}
	}
	return (false);
}

bool	Channel::setChatter(const std::string &nickname, bool add)
{
	if (add)
	{
		const User *user = this->_getUser(nickname);
		if (user)
		{
			this->_listAllowedChatters.push_back(user);
			return (true);
		}
	}
	else
	{
		for (std::vector<const User *>::iterator it = this->_listAllowedChatters.begin(); it < this->_listAllowedChatters.end(); it++)
		{
			if ((*it)->getNickname() == nickname)
			{
				this->_listAllowedChatters.erase(it);
				return (true);
			}
		}
	}
	return (false);
}

bool	Channel::isAllowedChatter(const User &user)
{
	return (std::find(this->_listAllowedChatters.begin(), this->_listAllowedChatters.end(), &user) != this->_listAllowedChatters.end());
}

void	Channel::invite(const User &user)
{
	this->_listInvites.push_back(&user);
}

bool	Channel::isOper(const User &user)
{
	return (std::find(this->_listOperators.begin(), this->_listOperators.end(), &user) != this->_listOperators.end());
}

bool	Channel::isInvited(const User &user)
{
	return (std::find(this->_listInvites.begin(), this->_listInvites.end(), &user) != this->_listInvites.end());
}

bool	Channel::isBanned(const User &user)
{
	for (size_t i = 0; i < this->_listBanMask.size(); i++)
	{
		if (checkMask(user.getNickname(), this->_listBanMask[i]))
		{
			return (true);
		}
	}
	return (false);
}
