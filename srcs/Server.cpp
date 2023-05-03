/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchini <ltrinchini@student.42lyon.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:01:13 by ltrinchi          #+#    #+#             */
/*   Updated: 2023/05/03 18:15:01 by ltrinchini       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, const char *password) : _password(password), _passwordOper("please"), _name("server")
{
	int on = true;
	this->_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1)
	{
		perror("Error on setsockopt()");
		close(this->_socket);
		exit(EXIT_FAILURE);
	}

	fcntl(this->_socket, F_SETFL, O_NONBLOCK);

	bzero((char *)&_address, sizeof(_address));
	this->_address.sin_family = AF_INET;
	this->_address.sin_port = htons(port);
	this->_address.sin_addr.s_addr = INADDR_ANY;

	if (bind(this->_socket, (const struct sockaddr *)&this->_address, (socklen_t)sizeof(this->_address)) == -1)
	{
		perror("Error on binding");
		close(this->_socket);
		exit(EXIT_FAILURE);
	}

	if (listen(this->_socket, MAX_BACKLOG) == -1)
	{
		perror("Error on listen");
		close(this->_socket);
		exit(EXIT_FAILURE);
	}

	std::cout << "---------------------" << std::endl;
	std::cout << "Server: UP" << std::endl;
	std::cout << "---------------------" << std::endl;
	print_IP();
	std::cout << "---------------------" << std::endl;
	std::cout << "Port [" << port << "]" << std::endl;
}

Server::~Server(void)
{
	close(this->_socket);
}

// PRIVATE
Server::iterator_user Server::_findUserIt(const int socket_fd)
{
	iterator_user userIt;
	for (userIt = this->_usersList.begin(); userIt != this->_usersList.end(); userIt++)
	{
		if ((*userIt).getSocket() == socket_fd)
			break;
	}
	return (userIt);
}

Server::iterator_pollfd Server::_findPollfd(const int socketFd)
{
	iterator_pollfd pollfdIt = this->_fds.begin();
	while (pollfdIt < this->_fds.end())
	{
		if ((*pollfdIt).fd == socketFd)
		{
			break;
		}
		pollfdIt++;
	}
	return (pollfdIt);
}

int Server::_acceptUser(iterator_pollfd &it)
{
	int socketFd;

	struct sockaddr_in tmpUserAddr;
	bzero(&tmpUserAddr, sizeof(tmpUserAddr));

	socklen_t userLength = sizeof(tmpUserAddr);

	while (true)
	{
		socketFd = accept(this->_socket, (struct sockaddr *)&tmpUserAddr, &userLength);
		if (socketFd < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				perror("Error accept");
				return (EXIT_FAILURE);
			}
			break;
		}

		User user(tmpUserAddr, userLength, socketFd);
		this->_usersList.push_back(user);

		struct pollfd tmpPollfd;
		bzero(&tmpPollfd, sizeof(tmpPollfd));
		tmpPollfd.fd = this->_usersList.back().getSocket();
		tmpPollfd.events = POLLIN;
		this->_fds.push_back(tmpPollfd);
		it = this->_fds.begin();

		std::cout << "Connect from " << inet_ntoa(tmpUserAddr.sin_addr) << std::endl;
	}
	return (EXIT_SUCCESS);
}

static std::string listNameCmd[] = {"PASS", "NICK", "USER", "PONG", "QUIT", "JOIN", "TOPIC", "PRIVMSG", "NOTICE", "PART", "MODE", "OPER", "NAMES", "LIST", "INVITE", "PING", "KICK", "KILL"};
static void (*funcCmd[])(User &user, Server &server, std::string &cmd) = {PASS, NICK, USER, PONG, QUIT, JOIN, TOPIC, PRIVMSG, PRIVMSG, PART, MODE, OPER, NAMES, LIST, INVITE, PING, KICK, KILL};

void Server::_executeCmd(std::string &command, User &user)
{
	std::vector<std::string> split = splitString(command, " ");
	if (split.empty())
	{
		return;
	}
	std::string nameCmd = split[0];
	for (size_t i = 0; i < sizeof(listNameCmd) / sizeof(std::string); i++)
	{
		if (nameCmd == listNameCmd[i])
		{
			if (i > 4 && !user.getRegisterStatus())
			{
				user.sendCmd(ERR_NOTREGISTERED());
				return;
			}
			funcCmd[i](user, *this, command);
			return;
		}
	}
	user.sendCmd(ERR_UNKNOWNCOMMAND(command));
}

void Server::_recvCmd(iterator_pollfd &client)
{
	int nb_of_bytes_recv = -1;
	char buff[BUFFER_SIZE] = {0};

	while (true)
	{
		nb_of_bytes_recv = recv((*client).fd, buff, sizeof(buff) - 1, MSG_DONTWAIT);
		if (nb_of_bytes_recv < 0)
		{
			if (errno == EWOULDBLOCK)
				break;
			perror("Error recv()");
			this->_closeConnection(client);
			return ;
		}
		buff[nb_of_bytes_recv] = 0;
	}

	User &user = *this->_findUserIt((*client).fd);
	user.setBuffCmd(user.getBuffCmd() + buff);

	std::vector<std::string> cmds = splitString(user.getBuffCmd(), "\r\n");

	size_t size = cmds.size();
	if ((user.getBuffCmd().size() > 2) && (user.getBuffCmd().find("\r\n", user.getBuffCmd().size() - 2) == std::string::npos))
	{
		size--;
	}
	for (size_t i = 0; i < size; i++)
	{
		this->_executeCmd(cmds[i], user);
		if (this->_findUserIt((*client).fd) != this->_usersList.end())
			user.setBuffCmd(user.getBuffCmd().substr(cmds[i].size() + 2, user.getBuffCmd().size() + 2 - cmds[i].size()));
	}
}

void Server::_closeConnection(iterator_pollfd &pollfdIt)
{
	iterator_user userIt = this->_findUserIt((*pollfdIt).fd);
	std::cout << "Disconnection of " << userIt->getAddressIP() << std::endl;
	close((*pollfdIt).fd);
	this->_usersList.erase(userIt);
	this->_fds.erase(pollfdIt);
	pollfdIt = this->_fds.begin();

}

void Server::_pingEachUser(void)
{
	for (iterator_user userIt = this->_usersList.begin(); userIt != this->_usersList.end(); userIt++)
	{
		if ((*userIt).checkTimeout())
		{
			(*userIt).sendCmd(ERR_PINGTIMEOUT());
			this->disconnectUser(*userIt);
			userIt = this->_usersList.begin();
		}
		else if ((*userIt).checkTimeToPing())
		{
			this->ping((*userIt), randomStr(10));
		}
	}
}

void Server::_cleanChannel(void)
{
	for (iterator_channel channelIt = this->_channelsList.begin(); channelIt != this->_channelsList.end(); channelIt++)
	{
		if ((*channelIt).getListMembers().size() == 0)
		{
			this->_channelsList.erase(channelIt);
			if (this->_channelsList.size() == 0)
			{
				break;
			}
			channelIt = this->_channelsList.begin();
		}
	}
}

void Server::_disconnectUser(const std::string &nickname)
{
	iterator_user userIt = this->findUserIt(nickname);
	iterator_pollfd pollfdIt = this->_findPollfd((*userIt).getSocket());

	this->_closeConnection(pollfdIt);
}

// PUBLIC
const std::list<User> &Server::getListUsers(void) const
{
	return (this->_usersList);
}

const std::vector<Channel> &Server::getListChannels(void) const
{
	return (this->_channelsList);
}

std::vector<Channel> &Server::getListChannels(void)
{
	return (this->_channelsList);
}

const std::string &Server::getName(void) const
{
	return (this->_name);
}

bool Server::checkPassword(const std::string &password) const
{
	return (password == this->_password);
}

bool Server::checkPasswordOper(const std::string &password) const
{
	return (password == this->_passwordOper);
}

bool Server::checkNicknameInUse(const std::string &nickname)
{
	for (iterator_user it = this->_usersList.begin(); it != this->_usersList.end(); it++)
	{
		if ((*it).getNickname() == nickname && (*it).getRegisterStatus())
		{
			return (true);
		}
	}
	return (false);
}

bool Server::checkIfChannelExist(const std::string &channelName)
{
	std::string tmp = channelName;
	std::transform(tmp.begin(), tmp.end(), tmp.begin(), tolower);
	for (iterator_channel it = this->_channelsList.begin(); it < this->_channelsList.end(); it++)
	{
		if ((*it).getName() == tmp)
			return (true);
	}
	return (false);
}

bool Server::_checkNickCollision(Server &server, User &user) const
{
	std::string nickname = user.getNickname();

	if (!server.checkNicknameInUse(nickname))
	{
		return (false);
	}
	else
	{
		user.sendCmd(ERR_NICKCOLLISION(nickname));
		server.disconnectUser(user);
	}

	while (server.checkNicknameInUse(nickname))
	{
		user = *server.findUserIt(nickname);
		user.sendCmd(ERR_NICKCOLLISION(nickname));
		server.disconnectUser(user);
	}
	return (true);
}

void Server::startServer(void)
{
	struct pollfd tmp_pollfd;

	bzero(&tmp_pollfd, sizeof(tmp_pollfd));
	tmp_pollfd.fd = this->_socket;
	tmp_pollfd.events = POLLIN;
	this->_fds.push_back(tmp_pollfd);

	while (true)
	{
		if (poll(&(*this->_fds.begin()), this->_fds.size(), TIMEOUT_POLL * 1000) == -1)
		{
			perror("Error poll");
			return;
		}

		for (Server::iterator_pollfd pollfdIt = this->_fds.begin(); pollfdIt < this->_fds.end(); pollfdIt++)
		{
			if ((*pollfdIt).fd == this->_socket && (*pollfdIt).events == POLLIN)
			{
				this->_acceptUser(pollfdIt);
			}
			else if ((*pollfdIt).revents == POLLIN)
			{
				this->_recvCmd(pollfdIt);
			}
			else if ((*pollfdIt).revents == POLLHUP + POLLIN)
			{
				this->disconnectUser(*this->_findUserIt(pollfdIt->fd));
			}
			else if ((*pollfdIt).revents != 0)
			{
				this->disconnectUser(*this->_findUserIt(pollfdIt->fd));
			}
		}

		this->_pingEachUser();
		this->_cleanChannel();
	}
}

void Server::ping(User &user, const std::string &msg) const
{
	user.setLastPing(msg);
	user.sendCmd("PING :" + msg);
}

void Server::connectUser(User &user)
{
	if (this->_checkNickCollision(*this, user))
	{
		return;
	}
	user.setConnectionTime(time(NULL));
	user.setRegisterStatus(true);

	// WELCOME
	user.sendCmd(RPL_WELCOME(user));
	user.sendCmd(RPL_YOURHOST(*this));
	user.sendCmd(RPL_CREATED());
	user.sendCmd(RPL_MYINFO(*this));

	// LUSERS
	user.sendCmd(RPL_LUSERCLIENT(*this));
	user.sendCmd(RPL_LUSEROP(*this));
	user.sendCmd(RPL_LUSERCHANNELS(*this));
	user.sendCmd(RPL_LUSERME(*this));

	// MOTD
	user.sendCmd(RPL_MOTDSTART(*this));
	std::ifstream file(MOTD_FILE);
	while (file)
	{
		std::string line;
		std::getline(file, line);
		user.sendCmd(RPL_MOTD(line));
	}
	user.sendCmd(RPL_ENDOFMOTD());
}

void Server::disconnectUser(const User &user, std::string message /* = QUIT_DFL_MSG */)
{
	iterator_pollfd pollfdIt = this->_findPollfd(user.getSocket());

	for (iterator_channel channelIt = this->_channelsList.begin(); channelIt < this->_channelsList.end(); channelIt++)
	{
		channelIt->sendCmd(user.getPrefix() + " QUIT " + message);
		channelIt->delUser(user);
	}

	this->_closeConnection(pollfdIt);
}

Channel &Server::findChannel(const std::string &channelName)
{
	std::string tmp = channelName;
	std::transform(tmp.begin(), tmp.end(), tmp.begin(), tolower);
	for (size_t i = 0; i < this->_channelsList.size(); i++)
	{
		if (this->_channelsList[i].getName() == tmp)
		{
			return (this->_channelsList[i]);
		}
	}
	Channel newChannel(tmp);
	this->_channelsList.push_back(newChannel);

	return (this->_channelsList.back());
}

Server::iterator_user Server::findUserIt(const std::string &nickname)
{
	iterator_user it = this->_usersList.begin();
	while (it != this->_usersList.end())
	{
		if ((*it).getNickname() == nickname)
			break;
		it++;
	}
	return (it);
}

std::vector<User *> Server::findUserByMask(const std::string &mask)
{
	std::vector<User *> listUsers;

	for (iterator_user userIt = this->_usersList.begin(); userIt != this->_usersList.end(); userIt++)
	{
		if (checkMask(((*userIt)).getNickname(), mask))
		{
			listUsers.push_back(&(*userIt));
		}
	}
	return (listUsers);
}

std::vector<Channel *> Server::findChannelByMask(const std::string &mask)
{

	std::string tmp = mask;
	std::transform(tmp.begin(), tmp.end(), tmp.begin(), tolower);

	std::vector<Channel *> listChannels;

	for (iterator_channel channelIt = this->_channelsList.begin(); channelIt < this->_channelsList.end(); channelIt++)
	{
		if (checkMask((*channelIt).getName(), tmp))
		{
			listChannels.push_back(&(*channelIt));
		}
	}

	return (listChannels);
}
