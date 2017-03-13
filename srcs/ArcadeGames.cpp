//
// ArcadeGames.cpp for arcade in /home/wurmel/rendu/cpp_arcade
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sat Mar 11 23:33:00 2017 Arnaud WURMEL
// Last update Mon Mar 13 15:42:53 2017 Arnaud WURMEL
//

#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include "Loader/Loader.hh"
#include "ArcadeGames.hpp"

Arcade::ArcadeGames::ArcadeGames(Arcade::IGraphic *graphic, Arcade::IGame *game)
{
  _game = game;
  _graphic = graphic;
  if (!_graphic && !_game)
    throw LoadingError("Library not respecting format");
}

void	Arcade::ArcadeGames::runGame()
{
  if (!_game || !_graphic)
    throw LoadingError("Missing library");
  
}

bool	Arcade::ArcadeGames::getMissingLibrary()
{
  std::cout << _game << std::endl;
  if (_game && !getGraphicLibrary())
    return false;
  if (!_game && !getGameLibrary())
    return false;
  return _game && _graphic;
}

Arcade::ILibrary	*Arcade::ArcadeGames::loadLibrary(std::string const& path) const
{
  Arcade::ILibrary	*lib;
  Arcade::Loader	loader;

  if (loader.loadLib(path.c_str()) == false) {
    throw LoadingError(std::string("Can't load librairie : ") + path);  
  }
  if ((lib = loader.getLibrary()) == NULL)
    throw LoadingError("Failed to retrieve librairie's instance");
  return (lib);
}

bool	Arcade::ArcadeGames::getGraphicLibrary(bool use_default)
{
  std::string	path;

  std::cout << "Here" << std::endl;
  if (use_default)
    {
      path = getFirstLibraryIn("./lib/");
      if (path.size() == 0)
	return false;
    }
  else
    path = _graphic->getLibraryPath();
  if (path.size() == 0)
    return false;
  
  return true;
}

std::string	Arcade::ArcadeGames::getFirstLibraryIn(const char *dir_path) const
{
  DIR		*dir;
  struct dirent	*dent;

  dir = opendir(dir_path);
  if (!dir)
    {
      std::cerr << "Can't load libraries directory" << std::endl;
      throw std::exception();
    }
  while ((dent = readdir(dir)))
    {
      if (dent->d_type == DT_REG && std::string(dent->d_name).find(".so") != std::string::npos)
	return (std::string(dent->d_name));
    }
  return (std::string(""));
}

bool	Arcade::ArcadeGames::getGameLibrary()
{
  ILibrary	*game;

  if (_graphic->renderWindowStart() == false)
    return false;
  game = loadLibrary("./games/" + _graphic->getGamePath());
  if (game->getLibraryType() != Arcade::GAME)
    throw LoadingError("Wrong library type expected game");
  _game = dynamic_cast<IGame *>(game);
  return true;
}

Arcade::ArcadeGames::~ArcadeGames()
{
  if (_graphic != NULL)
    delete _graphic;
  if (_game != NULL)
    delete _game;
}
