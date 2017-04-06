##
## Makefile for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libsokoban
## 
## Made by Victorien Fischer
## Login   <victorien.fischer@epitech.eu>
## 
## Started on  Wed Apr  5 13:03:25 2017 Victorien Fischer
## Last update Thu Apr  6 15:41:24 2017 Victorien Fischer
##

CC		=	g++

RM		=	rm -f

SRCS_PATH	=	srcs/

COMMON_PATH	=	../../Common/

SRCS		=	$(SRCS_PATH)mandatory.cpp			\
			$(COMMON_PATH)Event/Event.cpp			\
			$(COMMON_PATH)ScoreManager/ScoreManager.cpp	\
			Sokoban/Sokoban.cpp				\
			Sokoban/Case.cpp				\
			Sokoban/Box.cpp					\
			Sokoban/Wall.cpp				\
			Sokoban/Storage.cpp

OBJS		=	$(SRCS:.cpp=.o)

CXXFLAGS	=	-Wall -Wextra -std=c++14 -fPIC -I Sokoban/ -I ../../Interfaces/ -I $(COMMON_PATH)Event/ -I $(COMMON_PATH)ScoreManager/

NAME		=	lib_arcade_sokoban.so

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -shared $(OBJS) -o $(NAME) $(CXXFLAGS) $(LD_FLAGS)
		mv $(NAME) ..

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) ../$(NAME)
		$(RM) $(NAME)

re:		fclean all
