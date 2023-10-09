NAME		=	ircserv	

CPPFLAGS	=	-Wall -Werror -Wextra -std=c++98 -g -fno-limit-debug-info

DIR_OBJ		=	obj

SRCS		:=	main.cpp

SRCS		:= $(SRCS:%=srcs/%)

OBJS		:=	$(addprefix $(DIR_OBJ)/, $(SRCS:%.c=%.o))

CC			:= c++

all:  $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $@
	@clear
	# @make header --no-print-directory

$(DIR_OBJ)/%.o: %.c 
	@mkdir -p $(@D)
	@$(CC) $(CPPFLAGS)  -c $< -o $@   

clean: 
	@rm -rf $(DIR_OBJ) 

fclean: clean 
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
