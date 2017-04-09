##
## Makefile for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libmaze
## 
## Made by Victorien Fischer
## Login   <victorien.fischer@epitech.eu>
## 
## Started on  Wed Apr  5 13:03:25 2017 Victorien Fischer
## Last update Sun Apr  9 16:22:40 2017 Victorien Fischer
##

CC		=	g++

RM		=	rm -f

SRCS_PATH	=	srcs/

COMMON_PATH	=	../../Common/

SRCS		=	$(SRCS_PATH)mandatory.cpp			\
			$(COMMON_PATH)Event/Event.cpp			\
			$(COMMON_PATH)ScoreManager/ScoreManager.cpp	\
			Maze/Maze.cpp					\
			Maze/Case.cpp					\
			Maze/Wall.cpp					\
			Maze/Player.cpp					\
			Maze/Destination.cpp				\
			Maze/MapManager.cpp

OBJS		=	$(SRCS:.cpp=.o)

CXXFLAGS	=	-Wall -Wextra -std=c++14 -fPIC -I Maze/ -I ../../Interfaces/ -I $(COMMON_PATH)Event/ -I $(COMMON_PATH)ScoreManager/

NAME		=	lib_arcade_maze.so

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
