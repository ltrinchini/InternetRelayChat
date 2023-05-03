# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 14:11:27 by ljourand          #+#    #+#              #
#    Updated: 2022/11/21 17:18:16 by ltrinchi         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

SRCS_WITHOUT_PATH =	main.cpp \
					split.cpp \
					printIP.cpp \
					randomStr.cpp \
					mask.cpp \
					checkChannelName.cpp \
					checkNickname.cpp \
					responses.cpp \
					toString.cpp

CLASS_WITHOUT_PATH = 	Channel.cpp \
						Server.cpp \
						User.cpp				

CMDS_CHANNEL_WITHOUT_PATH =	INVITE.cpp \
							JOIN.cpp \
							KICK.cpp \
							LIST.cpp \
							MODE.cpp \
							NAMES.cpp \
							PART.cpp \
							TOPIC.cpp

CMDS_CONNECTION_WITHOUT_PATH =	NICK.cpp \
								OPER.cpp \
								PASS.cpp \
								QUIT.cpp \
								USER_CMD.cpp

CMDS_MISCELL_WITHOUT_PATH =	KILL.cpp \
							PING.cpp \
							PONG.cpp

CMDS_SENDING_WITHOUT_PATH =	PRIVMSG.cpp

OBJS_SRCS_WITHOUT_PATH = $(SRCS_WITHOUT_PATH:.cpp=.o)
OBJS_CLASS_WITHOUT_PATH = $(CLASS_WITHOUT_PATH:.cpp=.o)
OBJS_CMDS_CHANNEL_WITHOUT_PATH = $(CMDS_CHANNEL_WITHOUT_PATH:.cpp=.o)
OBJS_CMDS_CONNECTION_WITHOUT_PATH = $(CMDS_CONNECTION_WITHOUT_PATH:.cpp=.o)
OBJS_CMDS_MISCELL_WITHOUT_PATH = $(CMDS_MISCELL_WITHOUT_PATH:.cpp=.o)
OBJS_CMDS_SENDING_WITHOUT_PATH = $(CMDS_SENDING_WITHOUT_PATH:.cpp=.o)

HEADER_WITHOUT_PATH = irc.hpp
HEADER_CLASS_WITHOUT_PATH = Channel.hpp \
							Server.hpp \
							User.hpp

PATH_TO_SRCS = ./srcs/
PATH_TO_CLASS = ./srcs/
PATH_TO_CMDS_CHANNEL = ./srcs/commandes/channel/
PATH_TO_CMDS_CONNECTION = ./srcs/commandes/connection/
PATH_TO_CMDS_MISCELL = ./srcs/commandes/miscell/
PATH_TO_CMDS_SENDING = ./srcs/commandes/sending/
PATH_TO_OBJS = ./objs/
PATH_TO_HEADER = ./includes/
PATH_TO_HEADER_CLASS = ./srcs/

SRCS = $(addprefix $(PATH_TO_SRCS), $(SRCS_WITHOUT_PATH))
CLASS = $(addprefix $(PATH_TO_CLASS), $(CLASS_WITHOUT_PATH))
CMDS_CHANNEL = $(addprefix $(PATH_TO_CMDS), $(CMDS_CHANNEL_WITHOUT_PATH))
CMDS_CONNECTION = $(addprefix $(PATH_TO_CMDS), $(CMDS_CONNECTION_WITHOUT_PATH))
CMDS_MISCELL = $(addprefix $(PATH_TO_CMDS), $(CMDS_MISCELL_WITHOUT_PATH))
CMDS_SENDING = $(addprefix $(PATH_TO_CMDS), $(CMDS_SENDING_WITHOUT_PATH))

OBJS_SRCS = $(addprefix $(PATH_TO_OBJS), $(OBJS_SRCS_WITHOUT_PATH))
OBJS_CLASS = $(addprefix $(PATH_TO_OBJS), $(OBJS_CLASS_WITHOUT_PATH))
OBJS_CMDS_CHANNEL = $(addprefix $(PATH_TO_OBJS), $(OBJS_CMDS_CHANNEL_WITHOUT_PATH))
OBJS_CMDS_CONNECTION = $(addprefix $(PATH_TO_OBJS), $(OBJS_CMDS_CONNECTION_WITHOUT_PATH))
OBJS_CMDS_MISCELL = $(addprefix $(PATH_TO_OBJS), $(OBJS_CMDS_MISCELL_WITHOUT_PATH))
OBJS_CMDS_SENDING = $(addprefix $(PATH_TO_OBJS), $(OBJS_CMDS_SENDING_WITHOUT_PATH))

OBJS =	$(OBJS_SRCS) \
		$(OBJS_CLASS) \
		$(OBJS_CMDS_CHANNEL) \
		$(OBJS_CMDS_CONNECTION) \
		$(OBJS_CMDS_MISCELL) \
		$(OBJS_CMDS_SENDING)

HEADER =	$(addprefix $(PATH_TO_HEADER), $(HEADER_WITHOUT_PATH))

	######### COMMANDS ###########
CC = c++
CFLAGS	= -Wall -Wextra -Werror -std=c++98 -pedantic
RM = rm -rf
	################################

	####### COLORS FOR PRINTF #######
GREEN 		= \033[0;32m
RED			= \033[0;91m
YELLOW      = \033[0;93m
WHITE       = \033[1;49;97m
	#################################

all: $(PATH_TO_OBJS) $(NAME)
	printf "$(GREEN)✅ $(NAME) is up to date$(WHITE) 👏\n"  

$(PATH_TO_OBJS):
	mkdir -p ./objs/

$(OBJS_SRCS):$(PATH_TO_OBJS)%.o	: $(PATH_TO_SRCS)%.cpp Makefile $(HEADER)
	printf "\033[2K\r$(YELLOW)⏳ Compiling:$(WHITE) $< 🤞"
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJS_CLASS):$(PATH_TO_OBJS)%.o	: $(PATH_TO_CLASS)%.cpp $(PATH_TO_HEADER_CLASS)%.hpp Makefile $(HEADER)
	printf "\033[2K\r$(YELLOW)⏳ Compiling:$(WHITE) $< 🤞"
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJS_CMDS_CHANNEL):$(PATH_TO_OBJS)%.o	: $(PATH_TO_CMDS_CHANNEL)%.cpp Makefile $(HEADER)
	printf "\033[2K\r$(YELLOW)⏳ Compiling:$(WHITE) $< 🤞"
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJS_CMDS_CONNECTION):$(PATH_TO_OBJS)%.o	: $(PATH_TO_CMDS_CONNECTION)%.cpp Makefile $(HEADER)
	printf "\033[2K\r$(YELLOW)⏳ Compiling:$(WHITE) $< 🤞"
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJS_CMDS_MISCELL):$(PATH_TO_OBJS)%.o	: $(PATH_TO_CMDS_MISCELL)%.cpp Makefile $(HEADER)
	printf "\033[2K\r$(YELLOW)⏳ Compiling:$(WHITE) $< 🤞"
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJS_CMDS_SENDING):$(PATH_TO_OBJS)%.o	: $(PATH_TO_CMDS_SENDING)%.cpp Makefile $(HEADER)
	printf "\033[2K\r$(YELLOW)⏳ Compiling:$(WHITE) $< 🤞"
	$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME): $(OBJS)
	printf "\n"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

git: fclean
	git add *
	git add -u
	git commit

clean:
	$(RM) $(PATH_TO_OBJS)
	printf "$(RED)👌 Files has been deleted in $(PATH_TO_OBJS) ($(NAME))$(WHITE)\n"  
	printf "$(GREEN)✅ Clean 👍$(WHITE)\n"  

fclean: clean
	$(RM) $(NAME)
	printf "$(RED)👌 $(NAME) has been deleted$(WHITE)\n"  

re: fclean all
.PHONY: all rsc git clean fclean re
.SILENT:
