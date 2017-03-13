##
## Makefile for cpp_arcade in /home/wurmel/rendu/cpp_arcade
## 
## Made by Arnaud WURMEL
## Login   <wurmel_a@epitech.net>
## 
## Started on  Thu Mar  9 16:34:27 2017 Arnaud WURMEL
## Last update Mon Mar 13 22:53:56 2017 Arnaud WURMEL
##

CC=		g++

SRCS_PATH=	srcs

COMMON_PATH=	../../Common/

SRCS=		$(SRCS_PATH)/mandatory.cpp \
		Button/Button.cpp \
		$(COMMON_PATH)Event/Event.cpp \
		SFMLWrapper/SFMLWrapper.cpp

OBJS=		$(SRCS:.cpp=.o)

CXXFLAGS+=	-Wall -Wextra -std=c++11 -fPIC -I ./Interface -I ./SFMLWrapper -I ./Button -I ../../Interfaces/ -I $(COMMON_PATH)Event/ -g

LD_FLAGS=	-lsfml-graphics -lsfml-window -lsfml-system

NAME=		lib_arcade_sfml.so

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
