##
## Makefile for cpp_arcade in /home/wurmel/rendu/cpp_arcade
## 
## Made by Arnaud WURMEL
## Login   <wurmel_a@epitech.net>
## 
## Started on  Thu Mar  9 16:34:27 2017 Arnaud WURMEL
## Last update Tue Apr  4 12:59:57 2017 Arnaud WURMEL
##

CC=		g++

SRCS_PATH=	srcs

COMMON_PATH=	../../Common/

SRCS=		$(SRCS_PATH)/mandatory.cpp \
		$(COMMON_PATH)GraphicElements/Button/Button.cpp \
		$(COMMON_PATH)GraphicElements/TextField/TextField.cpp \
		$(COMMON_PATH)GraphicElements/HeritableObject/Selectable.cpp \
		$(COMMON_PATH)StartScreen/StartScreen.cpp \
		$(COMMON_PATH)Event/Event.cpp \
		$(COMMON_PATH)ScoreManager/ScoreManager.cpp \
		LapinWrapper/LapinWrapper.cpp \
		LapinHelper/LapinHelper.cpp

OBJS=		$(SRCS:.cpp=.o)

CXXFLAGS+=	-Wall -Wextra -std=c++14 -fPIC -I ./Interface -I ./LapinWrapper -I ../../Interfaces/ -I $(COMMON_PATH)Event/ -I $(COMMON_PATH)ScoreManager/ -I $(COMMON_PATH)GraphicElements -I $(COMMON_PATH)GraphicElements/HeritableObject/ -I $(COMMON_PATH)GraphicElements/Button/ -I $(COMMON_PATH)StartScreen -I ./LapinHelper

LD_FLAGS=	-lsfml-system -lsfml-window -lsfml-graphics -llapin -L ${HOME}/.froot/lib/ -lusb -lstdc++

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
