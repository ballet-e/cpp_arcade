##
## Makefile for cpp_arcade in /home/wurmel/rendu/cpp_arcade
##
## Made by Arnaud WURMEL
## Login   <wurmel_a@epitech.net>
##
## Started on  Thu Mar  9 16:34:27 2017 Arnaud WURMEL
## Last update Mon Apr  3 11:16:56 2017 Ballet Erwan
##

CC=		g++

SRCS_PATH=	srcs

COMMON_PATH=	../../Common/

SRCS=		$(SRCS_PATH)/mandatory.cpp \
				LIBLAPINWrapper/LIBLAPINWrapper.cpp

OBJS=		$(SRCS:.cpp=.o)

CXXFLAGS+=	-Wall -Wextra -std=c++14 -fPIC -I ./Interface -I ./LIBLAPINWrapper -I ../../Interfaces/ -I $(COMMON_PATH)Event/ -I $(COMMON_PATH)ScoreManager/ -I $(COMMON_PATH)GraphicElements -I $(COMMON_PATH)GraphicElements/HeritableObject/ -I $(COMMON_PATH)GraphicElements/Button/ -I $(COMMON_PATH)StartScreen -I ~/.froot/include/ -llapin -L ~/.froot/lib/ -g

LD_FLAGS=		-lsfml-graphics -lsfml-audio -lsfml-window \
						-lsfml-system -lstdc++ -lm -ldl -lpthread

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
