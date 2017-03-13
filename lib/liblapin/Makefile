##
## Makefile for cpp_arcade in /home/wurmel/rendu/cpp_arcade
##
## Made by Arnaud WURMEL
## Login   <wurmel_a@epitech.net>
##
## Started on  Thu Mar  9 16:34:27 2017 Arnaud WURMEL
## Last update Mon Mar 13 17:49:11 2017 Ballet Erwan
##

CC=		g++

SRCS_PATH=	srcs

SRCS=		$(SRCS_PATH)/mandatory.cpp \
				LIBLAPINWrapper/LIBLAPINWrapper.cpp

OBJS=		$(SRCS:.cpp=.o)

CXXFLAGS+=	-I ./Include -I ./LIBLAPINWrapper -I ./Interface -Wall -Wextra -std=c++11 -fPIC

LD_FLAGS=		-lsfml-graphics -lsfml-audio -lsfml-window \
						-lsfml-system -lstdc++ -lm -ldl -lpthread -llapin -L ~/.froot/lib

NAME=		lib_arcade_lapin.so

$(NAME):	$(OBJS)
		$(CC) -shared $(OBJS) -o $(NAME) $(CXXFLAGS) $(LD_FLAGS)
		mv $(NAME) ..

all:		$(NAME)

clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f ../$(NAME)
		rm -f $(NAME)

re:		fclean all
