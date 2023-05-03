/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:42 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/11/21 13:23:29 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef USER_HPP
# define USER_HPP

# define OPERATOR 1
# define WALLOPS 2
# define NOTICERECEIVER 4
# define INVISIBLE 8
# define AWAY 16

# include "../includes/irc.hpp"

class User {
	private:

		// Accept
		struct sockaddr_in	_address;
		socklen_t			_addressLength;
		int					_socket;

		std::string			_buffCmd;

		// CMD PASS
		std::string			_password;

		// CMD NICK
		std::string			_nickname;

		// CMD USER
		std::string			_username;
		std::string			_servername;
		std::string			_realname;
		std::time_t			_connectionTime;

		// CMD PING
		std::string			_lastPingMsg;
		std::time_t			_timeLastPing;
		std::time_t			_timeLastPong;

		char				_flags;

		bool				_isRegistered;
		bool				_PASSIsSet;
		bool				_NICKIsSet;
		bool				_USERIsSet;
		
		User(void);
	
	public:
		User(const User &copy);
		User(const struct sockaddr_in &address, const socklen_t &addressLength, int socket);
		~User(void);
		
		// Overload
		bool	operator==(const User &comp);
		bool	operator==(const std::string &nickname);

		// Accessors
		// Getters
		const int					&getSocket(void) const;
		const std::string			&getBuffCmd(void) const;
		const std::string			&getPassword(void) const;
		const std::string			&getNickname(void) const;
		const std::string			&getUsername(void) const;
		const std::string 			getAddressIP(void) const;
		bool						getRegisterStatus(void) const;

		// Flags
		// getters
		bool	isInvisible(void) const;
		bool	isOper(void) const;
		bool	isWallops(void) const;
		bool	isNoticeReceiver(void) const;
		bool	isAway(void) const;
		// setters
		void		setInvisible(bool status);
		void		setOper(bool status);
		void		setWallops(bool status);
		void		setNoticeReceiver(bool status);
		void		setAway(bool status);

		// Setters
		void	setBuffCmd(const std::string &cmd);
		void	setPassword(const std::string &password);
		void	setNickname(const std::string &nickname);
		void	setUsername(const std::string &username);
		void	setRealname(const std::string &realname);
		void	setRegisterStatus(const bool &status);
		void	setConnectionTime(const std::time_t &time);
		void	setTimeLastPing(void);
		void	setTimeLastPong(void);

		
		// Member functions
		bool	canRegister(void);
		void	sendCmd(std::string cmd) const;

		// Ping Pong
		void	setLastPing(const std::string str);
		bool	checkTimeout(void);
		bool	checkTimeToPing(void);
		bool	checkPingMsg(const std::string &msg);

		const std::string	getPrefix(void) const;
};

#endif
