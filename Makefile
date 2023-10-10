NAME		=	ircserv	

CPPFLAGS	=	-Wall -Werror -Wextra -std=c++98 -g# -fno-limit-debug-info

DIR_OBJ		=	obj

SRCS		:=	main.cpp user.cpp channel.cpp parser.cpp

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
