##
## Makefile for cpp_arcade in /home/wurmel/rendu/cpp_arcade
##
## Made by Arnaud WURMEL
## Login   <wurmel_a@epitech.net>
##
## Started on  Thu Mar  9 16:34:27 2017 Arnaud WURMEL
## Last update Sun Apr  9 21:10:17 2017 Arnaud WURMEL
##

CC=		g++

SRCS_PATH=	srcs

COMMON_PATH=	../../Common/

SRCS=		$(SRCS_PATH)/mandatory.cpp \
		$(COMMON_PATH)Event/Event.cpp \
		$(COMMON_PATH)ScoreManager/ScoreManager.cpp \
		SolarFox/SolarFox.cpp \
		SolarFox/Bullet.cpp \
		SolarFox/Enemy.cpp

OBJS=		$(SRCS:.cpp=.o)

CXXFLAGS+=	-Wall -Wextra -std=c++14 -fPIC -I ./SolarFox -I ./Button -I ../../Interfaces/ -I $(COMMON_PATH)Event/ -I $(COMMON_PATH)ScoreManager/

NAME=		lib_arcade_solar_fox.so

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
