//
// main.cpp for cpp_arcade in /home/wurmel/rendu/cpp_arcade
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Thu Mar  9 16:27:05 2017 Arnaud WURMEL
// Last update Fri Mar 10 20:30:29 2017 Arnaud WURMEL
//

#include <iostream>
#include "Loader/Loader.hh"

int	main(int ac, char **av)
{
  Arcade::Loader	loader;

  if (ac != 2) {
    loader.displayMessage("Usage :\n./arcade [LIB_PATH || GAME_PATH]", Arcade::Loader::UNDEFINED);
    return 84;
  }
  loader.displayMessage("Loading", Arcade::Loader::SUCCESS);
  return 0;
}
