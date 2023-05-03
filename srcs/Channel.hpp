/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:57:15 by ljourand          #+#    #+#             */
/*   Updated: 2022/11/18 16:28:52 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "../includes/irc.hpp"

# define PRIVATE 1
# define SECRET 2
# define INVITEONLY 4
# define TOPICSETTABLEOPER 8
# define OUTSIDEMSGALLOWED 16
# define MODERATED 32

class Channel
{
	public:
		typedef std::vector<const User *>::iterator iterator;
		
	private:
		std::string	_channelName;
		std::string	_key;
		std::string _topic;

		char						_flags;
		int							_userLimit;
		std::vector<std::string>	_listBanMask;
		std::vector<const User *>	_listMembers;
		std::vector<const User *>	_listOperators;
		std::vector<const User *>	_listInvites;
		std::vector<const User *>	_listAllowedChatters;

		const User	*_getUser(const std::string &nickname) const;
		
	public:
		Channel(const std::string &name);
		~Channel(void);

		const std::string					&getName(void) const;
		const std::string					&getTopic(void) const;
		const std::vector<const User *>		&getListMembers(void) const;
		const std::vector<std::string>		&getListBanMask(void) const;
		const std::vector<const User *>		&getListInvites(void) const;

		void	setTopic(const std::string &topic);
		
		void	addUser(const User &user);
		void	delUser(const User &user);
		void	sendCmd(const std::string &cmd);
		void	sendCmd(const std::string &cmd, const User &sender);
		bool	checkUserIn(const std::string &nickname);
		bool	checkUserIn(const User &user);

		// Flags
		// getters
		bool	isPrivate(void) const;
		bool	isSecret(void) const;
		bool	isInviteOnly(void) const;
		bool	isTopicSettableOper(void) const;
		bool	isOutsideMsgAllowed(void) const;
		bool	isModerated(void) const;
		
		// setters
		void	setPrivate(bool status);
		void	setSecret(bool status);
		void	setInviteOnly(bool status);
		void	setTopicSettableOper(bool status);
		void	setOutsideMsgAllowed(bool status);
		void	setModerated(bool status);

		int		getUserLimit(void) const;
		void	setUserLimit(const int limit);

		void	setBanMask(const std::string &banMask, bool add);
		
		const std::string	&getKey(void) const;
		void				setKey(const std::string &key, bool add);
		bool				checkKey(const std::string &key);

		bool	setOperator(const std::string &nickname, bool add);		
		bool	setChatter(const std::string &nickname, bool add);
		bool	isAllowedChatter(const User &user);

		void	invite(const User &user);

		bool	isBanned(const User &user);
		bool	isOper(const User &user);
		bool	isInvited(const User &user);
};

#endif
