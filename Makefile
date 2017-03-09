##
## Makefile for cpp_arcade in /home/wurmel/rendu/cpp_arcade
## 
## Made by Arnaud WURMEL
## Login   <wurmel_a@epitech.net>
## 
## Started on  Thu Mar  9 16:34:27 2017 Arnaud WURMEL
## Last update Thu Mar  9 16:36:53 2017 Arnaud WURMEL
##

CC=		g++

SRCS=		srcs/main.cpp

OBJS=		$(SRCS:.cpp=.o)

CXXFLAGS+=	-I ./Includes -Wall -Wextra -std=c++11

NAME=		arcade

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(CXXFLAGS)

all:		$(NAME)


clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f $(NAME)

re:		fclean all
