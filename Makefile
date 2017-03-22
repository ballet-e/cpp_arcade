##
## Makefile for cpp_arcade in /home/wurmel/rendu/cpp_arcade
## 
## Made by Arnaud WURMEL
## Login   <wurmel_a@epitech.net>
## 
## Started on  Thu Mar  9 16:34:27 2017 Arnaud WURMEL
## Last update Wed Mar 22 22:28:21 2017 Arnaud WURMEL
##

CC=		g++

SRCS_PATH=	srcs

SRCS=		$(SRCS_PATH)/main.cpp \
		$(SRCS_PATH)/Loader/Loader.cpp \
		$(SRCS_PATH)/ArcadeGames.cpp \
		$(SRCS_PATH)/Errors/Loading/LoadingError.cpp

OBJS=		$(SRCS:.cpp=.o)

CXXFLAGS+=	-I ./Includes -Wall -Wextra -std=c++11 -I ./Interfaces -I ./Common/Event/

LD_FLAGS+=	-ldl

NAME=		arcade

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(CXXFLAGS) $(LD_FLAGS)
		make -C ./games/
		make -C ./lib

all:		$(NAME)


clean:
		rm -f $(OBJS)
		make -C ./lib clean
		make -C ./games/ clean

fclean:		clean
		rm -f $(NAME)
		make -C ./lib fclean
		make -C ./games/ fclean

re:		fclean all
