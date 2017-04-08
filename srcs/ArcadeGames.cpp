//
// ArcadeGames.cpp for arcade in /home/wurmel/rendu/cpp_arcade
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sat Mar 11 23:33:00 2017 Arnaud WURMEL
// Last update Sat Apr  8 15:42:52 2017 Arnaud WURMEL
//

#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <vector>
#include "Loader/Loader.hh"
#include "ArcadeGames.hpp"

Arcade::ArcadeGames::ArcadeGames(Arcade::IGraphic *graphic, Arcade::IGame *game,
				 std::string const& path)
{
  _game_path = "";
  _lib_path = "";
  _pseudo = "";
  _game = game;
  _graphic = graphic;
  if (graphic)
    _lib_path = path;
  else
    _game_path = path;
  if (!_graphic && !_game)
    throw LoadingError("Library does not respect the correct format");
  _callback.insert(std::make_pair(Arcade::ExitStatus::NextLib, std::bind(&Arcade::ArcadeGames::loadNextLib, this)));
  _callback.insert(std::make_pair(Arcade::ExitStatus::PrevLib, std::bind(&Arcade::ArcadeGames::loadPrevLib, this)));
  _callback.insert(std::make_pair(Arcade::ExitStatus::NextGame, std::bind(&Arcade::ArcadeGames::loadNextGame, this)));
  _callback.insert(std::make_pair(Arcade::ExitStatus::PrevGame, std::bind(&Arcade::ArcadeGames::loadPrevGame, this)));
  _callback.insert(std::make_pair(Arcade::ExitStatus::BackMenu, std::bind(&Arcade::ArcadeGames::backToMenu, this)));
}

void	Arcade::ArcadeGames::runGame()
{
  Arcade::ExitStatus	e;

  if (!_game || !_graphic)
    throw LoadingError("Missing library");
  e = _graphic->renderWindowGame(1200, 900, _game);
  if (e != Arcade::ExitStatus::Exit)
    {
      if (handleExitStatus(e) == false)
	return ;
      if (getMissingLibrary() == false)
	return ;
      runGame();
    }
}

bool	Arcade::ArcadeGames::getMissingLibrary()
{
  if (_game && _graphic)
    return true;
  if (_game && !getGraphicLibrary(true))
    return false;
  else if (!_game && !getGameLibrary())
    return false;
  return _game && _graphic;
}

Arcade::ILibrary	*Arcade::ArcadeGames::loadLibrary(std::string const& path) const
{
  Arcade::ILibrary	*lib;
  Arcade::Loader	loader;

  if (loader.loadLib(path.c_str()) == false) {
    throw LoadingError(std::string("Can't load librairy : ") + path);  
  }
  if ((lib = loader.getLibrary()) == NULL)
    throw LoadingError("Failed to retrieve librairy's instance");
  return (lib);
}

bool	Arcade::ArcadeGames::getGraphicLibrary(bool use_default, std::string path)
{
  Arcade::ILibrary	*lib;

  if (use_default)
    {
      path = getFirstLibraryIn("./lib/");
      if (path.size() == 0)
	return false;
    }
  else if (path.size() == 0)
    path = _graphic->getLibraryPath();
  lib = loadLibrary("./lib/" + path);
  std::cout << "Path : " << path << std::endl;
  if (lib->getLibraryType() != Arcade::GRAPHIC)
    throw LoadingError("Wrong library type. Expected game");
  if (_graphic)
    delete _graphic;
  _graphic = static_cast<Arcade::IGraphic *>(lib);
  _lib_path = path;
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
    throw Arcade::LoadingError("Can't open libraries directory");
  while ((dent = readdir(dir)))
    {
      if (dent->d_type == DT_REG && std::string(dent->d_name).find(".so") != std::string::npos)
	return (std::string(dent->d_name));
    }
  return (std::string(""));
}

bool	Arcade::ArcadeGames::setUpGames(std::string const& path)
{
  ILibrary	*game;

  game = loadLibrary("./games/" + path);
  if (game->getLibraryType() != Arcade::GAME)
    throw LoadingError("Wrong library type. Expected game");
  if (_game)
    delete _game;
  _game = static_cast<IGame *>(game);
  _game_path = path;
  _game->setUpPseudo(_pseudo);
  return true;
}

bool	Arcade::ArcadeGames::getGameLibrary()
{
  if (_graphic->renderWindowStart() == false)
    return false;
  _pseudo = _graphic->getPseudo();
  setUpGames(_graphic->getGamePath());
  return (getGraphicLibrary());
}

std::vector<std::string>
Arcade::ArcadeGames::getLibraryForDirectory(std::string const& directory) const
{
  std::vector<std::string>	res;
  DIR		*dir;
  struct dirent	*dent;

  dir = opendir(directory.c_str());
  if (!dir)
    throw Arcade::LoadingError("Can't open libraries directory");
  while ((dent = readdir(dir)))
    {
      if (dent->d_type == DT_REG &&
	  std::string(dent->d_name).find(".so") != std::string::npos)
	{
	  res.push_back(std::string(dent->d_name));
	}
    }
  closedir(dir);
  return res;
}

bool	Arcade::ArcadeGames::handleExitStatus(Arcade::ExitStatus const& status)
{
  if (_callback.find(status) != _callback.end())
    return _callback[status]();
  else
    std::cerr << "Undefined callback : " << status << std::endl;
  return false;
}

bool	Arcade::ArcadeGames::loadNextLib()
{
  std::vector<std::string>	libs;
  unsigned int	idx;

  libs = getLibraryForDirectory("./lib/");
  if (libs.size() == 0)
    return false;
  idx = 0;
  while (idx < libs.size())
    {
      if (libs[idx].compare(_lib_path) == 0)
	return getGraphicLibrary(false, libs[(idx + 1) % libs.size()]);
      ++idx;
    }
  return false;
}

bool	Arcade::ArcadeGames::loadPrevLib()
{
  std::vector<std::string>	libs;
  unsigned int	idx;

  libs = getLibraryForDirectory("./lib/");
  if (libs.size() == 0)
    return false;
  idx = 0;
  while (idx < libs.size())
    {
      if (libs[idx].compare(_lib_path) == 0)
	{
	  if (idx > 0)
	    return getGraphicLibrary(false, libs[(idx - 1) % libs.size()]);
	  else
	    return getGraphicLibrary(false, libs[libs.size() - 1]);
	}
      ++idx;
    }
  return false;
}

bool	Arcade::ArcadeGames::loadNextGame()
{
  std::vector<std::string>	libs;
  unsigned int	idx;

  libs = getLibraryForDirectory("./games/");
  if (libs.size() == 0)
    return false;
  idx = 0;
  while (idx < libs.size())
    {
      if (libs[idx].compare(_game_path) == 0)
	return setUpGames(libs[(idx + 1) % libs.size()]);
      ++idx;
    }
  return false;
}

bool	Arcade::ArcadeGames::loadPrevGame()
{
  std::vector<std::string>	libs;
  unsigned int	idx;

  libs = getLibraryForDirectory("./games/");
  if (libs.size() == 0)
    return false;
  idx = 0;
  while (idx < libs.size())
    {
      if (libs[idx].compare(_game_path) == 0)
	{
	  if (idx > 0)
	    return setUpGames(libs[(idx - 1) % libs.size()]);
	  else
	    return setUpGames(libs[libs.size() - 1]);
	}
      ++idx;
    }
  return false;
}

bool	Arcade::ArcadeGames::backToMenu()
{
  if (_game)
    {
      delete _game;
      _game = NULL;
    }
  return true;
}

Arcade::ArcadeGames::~ArcadeGames()
{
  if (_graphic != NULL)
    delete _graphic;
  if (_game != NULL)
    delete _game;
}
