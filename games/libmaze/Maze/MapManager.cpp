//
// MapManager.cpp for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libsokoban/Sokoban
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Thu Apr  6 20:49:16 2017 Victorien Fischer
// Last update Sun Apr  9 16:42:48 2017 Victorien Fischer
//

#include <fstream>
#include <sstream>
#include <iostream>
#include "Wall.hh"
#include "Player.hh"
#include "Destination.hh"
#include "MapManager.hh"

/*
** ===== > CONSTRUCTOR
*/
Arcade::MapManager::MapManager()
{
  _width = 0;
  _height = 0;
  _creators.insert(std::make_pair('D', &Arcade::MapManager::createDestination));
  _creators.insert(std::make_pair('#', &Arcade::MapManager::createWall));
  _creators.insert(std::make_pair('P', &Arcade::MapManager::createPlayer));
}

Arcade::MapManager::~MapManager()
{}

/*
** ===== > CREATORS
*/
Arcade::Case	*Arcade::MapManager::createWall(int x, int y)
{
  return (new Case(x, y, new Wall, NULL));
}

Arcade::Case	*Arcade::MapManager::createPlayer(int x, int y)
{
  return (new Case(x, y, new Player, NULL));
}

Arcade::Case	*Arcade::MapManager::createDestination(int x, int y)
{
  return (new Case(x, y, NULL, new Destination));
}

/*
** ===== > GETTERS
*/
 Arcade::Case	*Arcade::MapManager::getCase(char t, int x, int y)
{
  std::map<char, Arcade::Case *(Arcade::MapManager::*)(int, int)>::iterator	it;

  it = _creators.find(t);
  if (it != _creators.end())
    return ((this->*((*it).second))(x, y));
  return (new Case(x, y, NULL, NULL));
}

int			Arcade::MapManager::getHeight() const
{
  return (_height);
}

int			Arcade::MapManager::getWidth() const
{
  return (_width);
}

/*
** ===== > SETTERS
*/
void			Arcade::MapManager::setMaxWidth(int width)
{
  if (width > _width)
    _width = width;
}

/*
** ===== > RETRIEVE MAP
*/
std::vector<Arcade::Case *>	Arcade::MapManager::retrieveMap(std::string const &filename)
{
  std::ifstream			mapFile;
  std::stringstream		strStream;
  std::string			buffer;
  std::string::iterator		it;
  std::vector<Arcade::Case *>	res;
  int				x;
  int				y;
  int				tab;

  x = 0;
  y = 0;
  mapFile.open(filename);
  if (mapFile.is_open())
    {
      strStream << mapFile.rdbuf();
      buffer = strStream.str();
      it = buffer.begin();
      while (it != buffer.end())
	{
	  if ((*it) == '\n')
	    {
	      y += 1;
	      setMaxWidth(x);
	      x = 0;
	    }
	  else
	    {
	      if ((*it) == '\t')
		{
		  tab = 7;
		  while (tab-- != 0)
		    res.push_back(getCase((*it), x++, y));
		}
	      res.push_back(getCase((*it), x, y));
	      x += 1;
	    }
	  it++;
	}
    }
  _height = y;
  return (res);
}


