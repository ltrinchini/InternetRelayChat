/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:56:19 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/11/21 11:33:57 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "../includes/irc.hpp"

class User;
class Channel;

class Server
{
	public:
		typedef std::vector<struct pollfd>::iterator	iterator_pollfd;
		typedef std::list<User>::iterator				iterator_user;
		typedef std::list<User>::const_iterator			const_iterator_user;
		typedef std::vector<Channel>::iterator			iterator_channel;
	
	private:
		int							_socket;
		struct	sockaddr_in			_address;
		std::list<User> 			_usersList;
		std::vector<struct pollfd>	_fds;
		std::vector<Channel> 		_channelsList;
		std::string					_password;

		std::string					_passwordOper;

		std::string					_name;

		iterator_user	_findUserIt(const int socket_fd);
		iterator_pollfd	_findPollfd(const int socketFd);

		// Member functions
		int				_acceptUser(iterator_pollfd &it);
		void			_executeCmd(std::string &command, User &user);
		void			_recvCmd(iterator_pollfd &client);
		void			_closeConnection(iterator_pollfd &pollfdIt);
		void			_pingEachUser(void);
		void			_cleanChannel(void);

		void			_disconnectUser(const std::string &nickname);
		bool			_checkNickCollision(Server &server, User &user) const;

	public:
		Server(int port, const char *password);
		~Server(void);

		// Getters
		const std::list<User>		&getListUsers(void) const;
		const std::vector<Channel>	&getListChannels(void) const;
		std::vector<Channel>		&getListChannels(void);
		const std::string			&getName(void) const;

		// Checkers
		bool					checkPassword(const std::string &password) const;
		bool					checkPasswordOper(const std::string &password) const;
		bool					checkNicknameInUse(const std::string &nickname);
		bool					checkIfChannelExist(const std::string &channelName);

		// Member functions
		void	startServer(void);
		void	ping(User &user, const std::string &msg) const;
		void	connectUser(User &user);
		void	disconnectUser(const User &user, std::string message = QUIT_DFL_MSG);

		std::vector<User *>		findUserByMask(const std::string &mask);
		std::vector<Channel *>	findChannelByMask(const std::string &mask);
		
		Channel 		&findChannel(const std::string &channelName);
		iterator_user	findUserIt(const std::string &nickname);
};

#endif
