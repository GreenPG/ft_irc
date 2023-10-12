# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlarraze <tlarraze@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/10 16:47:27 by tlarraze          #+#    #+#              #
#    Updated: 2023/10/12 12:27:11 by gpasquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ircserv	

CPPFLAGS	=	-Wall -Werror -Wextra -std=c++98 -g -fno-limit-debug-info

DIR_OBJ		=	obj

SRCS		=	main.cpp \
				server.cpp \
				user.cpp \
				channel.cpp \
				sendMessage.cpp \
				parser.cpp \
				commands/cap.cpp \
				commands/join.cpp \
				commands/pass.cpp \
				commands/nick.cpp \
				commands/user_command.cpp \
				commands/privmsg.cpp \
				commands/mode.cpp \
				commands/invite.cpp \
				commands/topic.cpp \
				commands/kick.cpp 

SRCS		:= $(SRCS:%=srcs/%)

OBJS		:=	$(addprefix $(DIR_OBJ)/, $(SRCS:%.cpp=%.o))

CC			:= c++

all:  $(NAME)

$(NAME): $(OBJS)
	$(info $(OBJS))
	@$(CC) $(CPPFLAGS) $(OBJS) -o $@
	@clear

$(DIR_OBJ)/%.o: %.cpp 
	$(info $(OBJS))
	@mkdir -p $(@D)
	@$(CC) $(CPPFLAGS) -c $< -o $@   

clean: 
	@rm -rf $(DIR_OBJ) 

fclean: clean 
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
