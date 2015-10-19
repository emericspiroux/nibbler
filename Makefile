#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvincent <jvincent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 18:33:50 by jvincent          #+#    #+#              #
#    Updated: 2015/05/28 11:00:06 by jvincent         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

RESET = 		\x1b[0m
RED = 			\x1b[33;01m
GREEN = 		\x1b[32;01m

CC = 			/usr/bin/g++

NAME = 			nibbler

CFLAGS = 		-Wall -Werror -Wextra

INC =			-I ./include \
				-I ./lib \

ifeq ($(USER), larry)
	SFMLLIB =
	INC +=
else ifeq ($(USER), jvincent)
	SFMLLIB = -L ~/.brew/Cellar/sfml/HEAD/lib
	INC += -I ~/.brew/Cellar/sfml/HEAD/include
endif

SFMLLIB +=		-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRCDIR =		source/
SRCSFILES =		main.cpp \
				getopt.class.cpp\
				gettest.class.cpp\
				Game.class.cpp\
				Apple.class.cpp\
				AEntities.class.cpp\
				MapTools.class.cpp\
				Snake.class.cpp

DYLD_LIBRARY_PATH=~/.brew/opt/sfml/lib/

DYLIBDIR =		lib/
DYLIB =			lib/libftcurse.dylib
DYLIB2 =		lib/libftsfml.dylib

DYLIBSRC =		LibftCurse.cpp
DYLIB2SRC =		LibftSfml.cpp

DYLIBSRCS =		$(addprefix $(DYLIBDIR), $(DYLIBSRC))
DYLIBOBJS =		$(DYLIBSRCS:.cpp=.o)
DYLIB2SRCS =	$(addprefix $(DYLIBDIR), $(DYLIB2SRC))
DYLIB2OBJS =	$(DYLIB2SRCS:.cpp=.o)

SRCS =			$(addprefix $(SRCDIR), $(SRCSFILES))
OBJS =			$(SRCS:.cpp=.o)

all: $(DYLIB) $(DYLIB2) $(NAME)

$(DYLIB): $(DYLIBOBJS)
	@$(CC) -o $(DYLIB) -shared -fPIC $(DYLIBOBJS) -lncurses && \
	echo "$(GREEN)Library successfully compiled$(RESET)" : $(DYLIB)

$(DYLIB2): $(DYLIB2OBJS)
	@$(CC) -o $(DYLIB2) -shared -fPIC $(DYLIB2OBJS) $(SFMLLIB) && \
	echo "$(GREEN)Library successfully compiled$(RESET)" : $(DYLIB2)

%.o: %.cpp
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@ && echo "[$(GREEN)OK$(RESET)] $<"

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS)
	@echo "$(GREEN)Binary successfully compiled$(RESET)" : $(NAME)

clean:
	@rm -f $(DYLIBOBJS) && echo "[$(RED)DEL$(RESET)] $(DYLIB) objects"
	@rm -f $(DYLIB2OBJS) && echo "[$(RED)DEL$(RESET)] $(DYLIB2) objects"
	@rm -f $(OBJS) && echo "[$(RED)DEL$(RESET)] $(NAME) objects"

fclean: clean
	@rm -f $(DYLIB) && echo "[$(RED)DEL$(RESET)] $(DYLIB)"
	@rm -f $(DYLIB2) && echo "[$(RED)DEL$(RESET)] $(DYLIB2)"
	@rm -f $(NAME) && echo "[$(RED)DEL$(RESET)] $(NAME)"

test: re
	@echo "" && echo "$(GREEN)./$(NAME)$(RESET)" && ./$(NAME)

re: fclean all

.PHONY: clean fclean re all

.SILENT:
