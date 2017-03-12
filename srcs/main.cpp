//
// main.cpp for cpp_arcade in /home/wurmel/rendu/cpp_arcade
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Thu Mar  9 16:27:05 2017 Arnaud WURMEL
// Last update Sun Mar 12 14:54:20 2017 Arnaud WURMEL
//

#include <iostream>
#include <string>
#include "Loader/Loader.hh"
#include "Errors/Error.hh"
#include "IGraphic.hh"

int	main(int ac, char **av)
{
  Arcade::Loader	loader;
  Arcade::IGraphic	*graphic = NULL;

  if (ac != 2) {
    loader.displayMessage("Usage :\n./arcade [LIB_PATH || GAME_PATH]", Arcade::Loader::UNDEFINED);
    return 84;
  }
  try {
    if (loader.loadLib(av[1]) == false) {
      throw Arcade::LoadingError(std::string("Can't load librairie : ") + av[1]);
    }
    loader.displayMessage("Loading", Arcade::Loader::SUCCESS);
    if ((graphic = loader.getLibrary()) == NULL)
      {
	loader.displayMessage("Get instance graphic", Arcade::Loader::ERROR);
	return 84;
      }
    loader.displayMessage("Get instance graphic", Arcade::Loader::SUCCESS);
  }
  catch (Arcade::LoadingError& e) {
    loader.displayMessage("Loading", Arcade::Loader::ERROR);
    std::cerr << e.what() << std::endl;
    if (graphic)
      delete graphic;
    return 84;
  }
  if (graphic->getLibraryType() == Arcade::Graphic)
    graphic->renderWindowStart();
  else
    std::cerr << "Start on game impossible" << std::endl;
  delete graphic;
  return 0;
}
