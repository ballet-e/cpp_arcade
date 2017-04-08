##
## Makefile for Arcade in /home/wurmel/rendu/cpp_arcade/lib
##
## Made by Arnaud WURMEL
## Login   <wurmel_a@epitech.net>
##
## Started on  Fri Mar 10 21:12:00 2017 Arnaud WURMEL
## Last update Sat Apr  8 17:40:20 2017 Arnaud WURMEL
##

all:
	make -C ./libsfml/
	make -C ./liblapin/
	make -C ./libncurses/

clean:
	make -C ./libsfml/ clean
	make -C ./liblapin/ clean
	make -C ./libncurses/ clean

fclean:
	make -C ./libsfml/ fclean
	make -C ./liblapin/ fclean
	make -C ./libncurses/ fclean

re:	fclean all
