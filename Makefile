#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 18:33:50 by jvincent          #+#    #+#              #
#    Updated: 2015/04/03 14:33:18 by jvincent         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

RESET = 		\x1b[0m
RED = 			\x1b[33;01m
GREEN = 		\x1b[32;01m

CC = 			/usr/bin/g++

NAME = 			nibbler

CFLAGS = 		-Wall -Werror -Wextra

INC =			-I ./include

SRCDIR =		source/
SRCSFILES =		main.cpp \
				getopt.class.cpp\
				gettest.class.cpp\
				Game.class.cpp\
				Apple.class.cpp\
				AEntities.class.cpp\
				MapTools.class.cpp\
				Snake.class.cpp

SRCS =			$(addprefix $(SRCDIR), $(SRCSFILES))
OBJS =			$(SRCS:.cpp=.o)

all: $(NAME)

%.o: %.cpp
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@ && echo "[$(GREEN)OK$(RESET)] $<"

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LFLAGS)
	@echo "$(GREEN)Binary successfully compiled$(RESET)" : $(NAME)

clean:
	@rm -f $(OBJS) && echo "[$(RED)DEL$(RESET)] $(NAME) objects"

fclean: clean
	@rm -f $(NAME) && echo "[$(RED)DEL$(RESET)] $(NAME)"

test: re
	@echo "" && echo "$(GREEN)./$(NAME)$(RESET)" && ./$(NAME)

re: fclean all

.PHONY: clean fclean re all

.SILENT:
