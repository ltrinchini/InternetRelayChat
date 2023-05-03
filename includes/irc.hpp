/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljourand <ljourand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:11:21 by ljourand          #+#    #+#             */
/*   Updated: 2022/11/18 15:54:00 by ljourand         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

# define BUFFER_SIZE 512
# define MAX_BACKLOG 5

# define TIMEOUT 120
# define TIME_TO_PING TIMEOUT * 0.8
# define TIMEOUT_POLL 1
# define MOTD_FILE "Ressources/MOTD.txt"

# define QUIT_DFL_MSG "disconnected from the server"
# define PART_DFL_MSG "left the room"
# define KICK_DFL_MSG "got kicked"

// JOIN
# define CTRL_G 7
# define SIZEMAX_CHANNEL_NAME 50

// Lib C
# include <stdlib.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <fcntl.h>
# include <poll.h>
# include <netdb.h>

// Lib CPP
# include <cstring>
# include <iostream>
# include <fstream>
# include <vector>
# include <list>
# include <cstdbool>
# include <ctime>
# include <sstream>

// Class
# include "../srcs/errorCodes.hpp"

# include "../srcs/User.hpp"
# include "../srcs/Server.hpp"
# include "../srcs/Channel.hpp"

//Commandes

void	PASS(User &user, Server &server, std::string &cmd);
void	NICK(User &user, Server &server, std::string &cmd);
void	USER(User &user, Server &server, std::string &cmd);
void	PONG(User &user, Server &server, std::string &cmd);
void	JOIN(User &user, Server &server, std::string &cmd);
void	TOPIC(User &user, Server &server, std::string &cmd);
void	PRIVMSG(User &user, Server &server, std::string &cmd);
void	PART(User &user, Server &server, std::string &cmd);
void	QUIT(User &user, Server &server, std::string &cmd);
void	MODE(User &user, Server &server, std::string &cmd);
void	OPER(User &user, Server &server, std::string &cmd);
void	NAMES(User &user, Server &server, std::string &cmd);
void	LIST(User &user, Server &server, std::string &cmd);
void	INVITE(User &user, Server &server, std::string &cmd);
void	KICK(User &user, Server &server, std::string &cmd);
void	PING(User &user, Server &server, std::string &cmd);
void	KILL(User &user, Server &server, std::string &cmd);

std::vector<std::string>	splitString(std::string str, std::string delimiter = " ");
std::vector<std::string> 	SplitStringKeep(std::string str, std::string delimiter = " ");

bool checkMask(const std::string &string, const std::string &mask);

void		replace_all(std::string &str,const std::string to_find, const std::string replace);
void		print_IP(void);
std::string	randomStr(size_t length);
std::string	toString(int nb);

bool	checkNickname(const std::string &nickname);
bool	checkChannelName(std::string &channelName);

#endif
