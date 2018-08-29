# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbouabou <bbouaboud@student.42.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/29 23:57:55 by bbouabou          #+#    #+#              #
#    Updated: 2018/08/30 00:05:10 by bbouabou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	g++

CFLAGS		=	-Wall -Wextra -Werror

DOBJ		=	obj/

INC			=	-I includes

NAME		=	Matt_daemon

SRCS		=	CDaemon.cpp Tintin_reporter.cpp main.cpp

SRCS_DIR	=	src/

OBJS		=	$(patsubst %.cpp, $(DOBJ)%.o, $(SRCS))

DEPS		=	$(patsubst %.cpp, $(DOBJ)%.d, $(SRCS))

DEPENDS		=	-MT $@ -MD -MP -MF $(subst .o,.d,$@)

all:		$(NAME)

$(NAME):	$(OBJS)
	@echo "\033[32m$(CC) \033[33m$(CFLAGS) \033[36m -o $(NAME) $(OBJS)\033[0m"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INC)
	@echo "\033[33mCompilation of $(NAME) : \033[32mSuccess\033[0m"

$(DOBJ)%.o:	$(SRCS_DIR)%.cpp
	@mkdir -p $(DOBJ)
	@echo "\033[32m$(CC) \033[33m$(CFLAGS) \033[35m$(DEPENDS) \033[36m-c $< -o $@ $(INC)\033[0m"
	@$(CC) $(CFLAGS) $(DEPENDS) -c $< -o $@ $(INC)

clean:
	@echo "\033[31mObjects of $(NAME) : deleted\033[0m"
	@/bin/rm -rf $(DOBJ)

fclean:		clean
	@echo "\033[31m$(NAME) : deleted\033[0m"
	@/bin/rm -f $(NAME)

re:			fclean all

.PHONY:		all re fclean clean
