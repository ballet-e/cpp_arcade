//
// main.cpp for cpp_arcade in /home/wurmel/rendu/cpp_arcade
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Thu Mar  9 16:27:05 2017 Arnaud WURMEL
// Last update Fri Apr  7 23:50:00 2017 Arnaud WURMEL
//

#include <iostream>
#include <string>
#include "Loader/Loader.hh"
#include "Errors/Error.hh"
#include "IGraphic.hh"
#include "ArcadeGames.hpp"

static void	display_ascii()
{
  std::cout << "    ___                        __   " << std::endl;
  std::cout << "   /   |  ______________ _____/ /__ " << std::endl;
  std::cout << "  / /| | / ___/ ___/ __ `/ __  / _ \\" << std::endl;
  std::cout << " / ___ |/ /  / /__/ /_/ / /_/ /  __/" << std::endl;
  std::cout << "/_/  |_/_/   \\___/\\__,_/\\__,_/\\___/ " << std::endl;
  std::cout << "\033[0m" << std::endl << std::endl;
}

int	main(int ac, char **av)
{
  Arcade::Loader	loader;
  Arcade::ILibrary	*graphic = NULL;
  Arcade::ArcadeGames	*root = NULL;

  display_ascii();
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
  catch (std::exception& e) {
    loader.displayMessage("Loading", Arcade::Loader::ERROR);
    std::cerr << e.what() << std::endl;
    if (graphic)
      delete graphic;
    return 84;
  }
  try {
    if (graphic->getLibraryType() == Arcade::GRAPHIC)
      root = new Arcade::ArcadeGames(dynamic_cast<Arcade::IGraphic *>(graphic), NULL, av[1]);
    else
      root = new Arcade::ArcadeGames(NULL, dynamic_cast<Arcade::IGame *>(graphic), av[1]);
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    delete graphic;
    return 84;
  }
  try {
    if (!root->getMissingLibrary())
      return (0);
    root->runGame();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    delete root;
    return 84;
  }
  delete root;
  return 0;
}
