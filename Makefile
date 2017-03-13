##
## Makefile for cpp_arcade in /home/wurmel/rendu/cpp_arcade
## 
## Made by Arnaud WURMEL
## Login   <wurmel_a@epitech.net>
## 
## Started on  Thu Mar  9 16:34:27 2017 Arnaud WURMEL
## Last update Mon Mar 13 12:36:33 2017 Arnaud WURMEL
##

CC=		g++

SRCS_PATH=	srcs

SRCS=		$(SRCS_PATH)/main.cpp \
		$(SRCS_PATH)/Loader/Loader.cpp \
		$(SRCS_PATH)/ArcadeGames.cpp \
		$(SRCS_PATH)/Errors/Loading/LoadingError.cpp

OBJS=		$(SRCS:.cpp=.o)

CXXFLAGS+=	-I ./Includes -Wall -Wextra -std=c++11 -I ./Interfaces -g

LD_FLAGS+=	-ldl

NAME=		arcade

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(CXXFLAGS) $(LD_FLAGS)
		make -C ./lib

all:		$(NAME)


clean:
		rm -f $(OBJS)
		make -C ./lib clean

fclean:		clean
		rm -f $(NAME)
		make -C ./lib fclean

re:		fclean all
