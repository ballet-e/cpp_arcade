//
// main.cpp for cpp_arcade in /home/wurmel/rendu/cpp_arcade
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Thu Mar  9 16:27:05 2017 Arnaud WURMEL
// Last update Fri Mar 10 20:45:03 2017 Arnaud WURMEL
//

#include <iostream>
#include <string>
#include "Loader/Loader.hh"
#include "Errors/Error.hh"

int	main(int ac, char **av)
{
  Arcade::Loader	loader;

  if (ac != 2) {
    loader.displayMessage("Usage :\n./arcade [LIB_PATH || GAME_PATH]", Arcade::Loader::UNDEFINED);
    return 84;
  }
  try {
    if (loader.loadLib(av[1]) == false) {
      throw Arcade::LoadingError(std::string("Can't load librairie : ") + av[1]);
    }
    loader.displayMessage("Loading", Arcade::Loader::SUCCESS);
  }
  catch (Arcade::LoadingError& e) {
    loader.displayMessage("Loading", Arcade::Loader::ERROR);
    std::cout << e.what() << std::endl;
    return 84;
  }
  return 0;
}
