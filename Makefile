##
## Makefile for cpp_arcade in /home/wurmel/rendu/cpp_arcade
## 
## Made by Arnaud WURMEL
## Login   <wurmel_a@epitech.net>
## 
## Started on  Thu Mar  9 16:34:27 2017 Arnaud WURMEL
## Last update Fri Mar 10 20:38:43 2017 Arnaud WURMEL
##

CC=		g++

SRCS_PATH=	srcs

SRCS=		$(SRCS_PATH)/main.cpp \
		$(SRCS_PATH)/Loader/Loader.cpp \
		$(SRCS_PATH)/Errors/Loading/LoadingError.cpp

OBJS=		$(SRCS:.cpp=.o)

CXXFLAGS+=	-I ./Includes -Wall -Wextra -std=c++11

LD_FLAGS+=	-ldl

NAME=		arcade

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(CXXFLAGS) $(LD_FLAGS)

all:		$(NAME)


clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f $(NAME)

re:		fclean all
