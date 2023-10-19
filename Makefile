# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/10 16:47:27 by tlarraze          #+#    #+#              #
#    Updated: 2023/10/19 15:30:00 by tlarraze         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ircserv	

BOT_NAME	= bot

CPPFLAGS	=	-Wall -Werror -Wextra -std=c++98 -g# -fno-limit-debug-info

DIR_OBJ		=	obj

SRCS		=	main.cpp \
				server.cpp \
				user.cpp \
				channel.cpp \
				sendMessage.cpp \
				parser.cpp \
				commands/join.cpp \
				commands/pass.cpp \
				commands/nick.cpp \
				commands/user_command.cpp \
				commands/privmsg.cpp \
				commands/mode.cpp \
				commands/invite.cpp \
				commands/topic.cpp \
				commands/skill.cpp \
				commands/utils.cpp \
				commands/quit.cpp \
				commands/kick.cpp 

SRCS		:= $(SRCS:%=srcs/server/%)

OBJS		:=	$(addprefix $(DIR_OBJ)/, $(SRCS:%.cpp=%.o))

SRCS_BOT	= 	main.cpp bot.cpp

SRCS_BOT	:= $(SRCS_BOT:%=srcs/bot/%)

OBJS_BOT	:= $(addprefix $(DIR_OBJ)/, $(SRCS_BOT:%.cpp=%.o))

CC			:= c++

all:  $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CPPFLAGS) $(OBJS) -o $@
	@clear
	@echo ".---..----------------------------------------------------------..----."
	@echo "|   ||.--------------------------------------------------------.||    |"
	@echo "| o |||                                                         ||| o |"
	@echo "| _ |||       ___          ________          ________           ||| _ |"
	@echo "|(_)|||      |\  \        |\   __  \        |\   ____\          |||(_)|"
	@echo "|   |||      \ \  \       \ \  \|\  \       \ \  \___|          |||   |"
	@echo "|.-.|||       \ \  \       \ \   _  _\       \ \  \             |||.-.|"
	@echo "| o |||        \ \  \       \ \   _  _\       \ \  \            ||| o |"
	@echo "| -'|||         \ \  \       \ \  \\\\\\  \|       \ \  \____       ||| -'|"
	@echo "|   |||          \ \__\       \ \__\\\\\\ _\        \ \_______\     |||   |"
	@echo "|.-.|||           \|__|        \|__|\|__|        \|_______|     |||.-.|"
	@echo "| O |||                                                         ||| O |"
	@echo "|\ -'||\ -------------------------------------------------------'|| -'|"
	@echo "\ ---'\ ---------------------------------------------------------' ---'"
	@echo "       _||_                                                  _||_"
	@echo "      /____\\                                                /____\\"
	@echo "________________________________________________________________________"

$(DIR_OBJ)/%.o: %.cpp 
	@mkdir -p $(@D)
	@$(CC) $(CPPFLAGS) -c $< -o $@   

bonus: $(BOT_NAME)

$(BOT_NAME): $(NAME) $(OBJS_BOT)
	@$(CC) $(CPPFLAGS) $(OBJS_BOT) -o $@

clean: 
	@rm -rf $(DIR_OBJ) 

fclean: clean 
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re
