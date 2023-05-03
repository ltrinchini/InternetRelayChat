/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:04:56 by ljourand          #+#    #+#             */
/*   Updated: 2022/11/21 13:53:33 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(void) : _addressLength(sizeof(this->_address)), _socket(-1), _isRegistered(false), _PASSIsSet(false), _NICKIsSet(false), _USERIsSet(false)
{
	bzero(&this->_address, this->_addressLength);
}

User::User(const struct sockaddr_in &address, const socklen_t &addressLength, int socket) : _address(address), _addressLength(addressLength), _socket(socket), _isRegistered(false), _PASSIsSet(false), _NICKIsSet(false), _USERIsSet(false)
{
	time(&this->_timeLastPing);
	this->_timeLastPing = time(NULL) + TIMEOUT;
	this->_timeLastPong = time(NULL);
	_flags = 0;
}

User::User(const User &copy) : _address(copy._address), _addressLength(copy._addressLength), _socket(copy._socket), _isRegistered(copy._isRegistered), _PASSIsSet(copy._PASSIsSet), _NICKIsSet(copy._NICKIsSet), _USERIsSet(copy._USERIsSet)
{
	_password = copy._password;
	_nickname = copy._nickname;
	_username = copy._username;
	_servername = copy._servername;
	_realname = copy._realname;
	_timeLastPing = copy._timeLastPing;
	_timeLastPong = copy._timeLastPong;
}

User::~User(void)
{
}

bool	User::operator==(const User &comp)
{
	return (this->_nickname == comp._nickname);
}

bool	User::operator==(const std::string &nickname)
{
	return (this->_nickname == nickname);
}

const int &User::getSocket(void) const
{
	return (this->_socket);
}

const std::string	&User::getBuffCmd(void) const
{
	return (this->_buffCmd);
}

const std::string &User::getPassword(void) const
{
	return (this->_password);
}

const std::string &User::getNickname(void) const
{
	return (this->_nickname);
}

const std::string &User::getUsername(void) const
{
	return (this->_username);
}

const std::string User::getAddressIP(void) const
{
	return(inet_ntoa(this->_address.sin_addr));
}

bool User::getRegisterStatus(void) const
{
	return (this->_isRegistered);
}

void User::setBuffCmd(const std::string &cmd)
{
	this->_buffCmd = cmd;
}

void User::setPassword(const std::string &password)
{
	this->_password = password;
	this->_PASSIsSet = true;
}

void User::setNickname(const std::string &nickname)
{
	this->_nickname = nickname;
	this->_NICKIsSet = true;
}

void User::setUsername(const std::string &username)
{
	this->_username = username;
	this->_USERIsSet = true;
}

void User::setRealname(const std::string &realname)
{
	this->_realname = realname;
}

void User::setRegisterStatus(const bool &status)
{
	this->_isRegistered = status;
}

void User::setConnectionTime(const std::time_t &time)
{
	this->_connectionTime = time;
}

void	User::setTimeLastPing(void)
{
	time(&this->_timeLastPing);
}

void	User::setTimeLastPong(void)
{
	time(&this->_timeLastPong);
}

bool User::canRegister(void)
{
	if (this->_PASSIsSet && this->_NICKIsSet && this->_USERIsSet && !this->_isRegistered)
	{
		return (true);
	}
	return (false);
}

void User::sendCmd(std::string cmd) const
{
	if (cmd[cmd.size() - 1] != '\n')
	{
		cmd = cmd + "\r\n";
	}
	
	if (send(this->_socket, cmd.c_str(), cmd.size(), MSG_DONTWAIT) == -1)
	{
		if (errno != EWOULDBLOCK)
		{
			perror("Error send");
		}
	}
}

void User::setLastPing(const std::string str)
{
	time(&this->_timeLastPing);
	this->_lastPingMsg = str;
}

bool User::checkTimeout(void)
{
	return (difftime(time(NULL), this->_timeLastPong) >= TIMEOUT);
}

bool User::checkTimeToPing(void)
{
	return (difftime(time(NULL), this->_timeLastPing) >= TIME_TO_PING);
}

bool User::checkPingMsg(const std::string &msg)
{
	std::string pingMsg = msg;
	if (pingMsg.at(0) == ':')
		pingMsg.erase(0, 1);

	if (this->_lastPingMsg == pingMsg)
		return (true);
	return (false);
}

const std::string	User::getPrefix(void) const
{
	return (":" + this->_nickname + "!" + this->_username + "@" + this->getAddressIP());
}

// Flags
// getters
bool	User::isInvisible(void) const
{
	return ((this->_flags & INVISIBLE) == INVISIBLE);
}

bool	User::isOper(void) const
{
	return ((this->_flags & OPERATOR) == OPERATOR);
}

bool	User::isWallops(void) const
{
	return ((this->_flags & WALLOPS) == WALLOPS);
}

bool	User::isNoticeReceiver(void) const
{
	return ((this->_flags & NOTICERECEIVER) == NOTICERECEIVER);
}

bool	User::isAway(void) const
{
	return ((this->_flags & AWAY) == AWAY);
}

// setters
void		User::setInvisible(bool status)
{
	if (status)
	{
		this->_flags |= INVISIBLE;
	}
	else
	{
		this->_flags &= ~INVISIBLE;
	}
}

void		User::setOper(bool status)
{
	if (status)
	{
		this->_flags |= OPERATOR;
	}
	else
	{
		this->_flags &= ~OPERATOR;
	}
}

void		User::setWallops(bool status)
{
	if (status)
	{
		this->_flags |= WALLOPS;
	}
	else
	{
		this->_flags &= ~WALLOPS;
	}
}

void		User::setNoticeReceiver(bool status)
{
	if (status)
	{
		this->_flags |= NOTICERECEIVER;
	}
	else
	{
		this->_flags &= ~NOTICERECEIVER;
	}
}

void		User::setAway(bool status)
{
	if (status)
	{
		this->_flags |= AWAY;
	}
	else
	{
		this->_flags &= ~AWAY;
	}
}
