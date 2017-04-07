//
// MapLoader.cpp for cpp_arcade in /home/wurmel_a/rendu/cpp_arcade/games/libwolf3d
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Thu Apr  6 18:29:28 2017 Arnaud WURMEL
// Last update Thu Apr  6 21:29:27 2017 Arnaud WURMEL
//

#include <iostream>
#include <fstream>
#include "MapLoader.hh"

Arcade::MapLoader::MapLoader()
{

}

std::vector<std::vector<std::shared_ptr<Arcade::Map>>> const&	Arcade::MapLoader::getMap()
{
  if (_map.size() > 0)
    return _map;
  loadFile();
  return _map;
}

void	Arcade::MapLoader::deleteMap()
{
  _map.clear();
}

void	Arcade::MapLoader::loadFile()
{
  std::string	line;
  std::ifstream	f;
  std::string::iterator	it;
  unsigned int	idx;

  _map.clear();
  idx = 0;
  f.open("Ressources/wolf3D/map.wolf");
  if (f.is_open())
    {
      while (std::getline(f, line))
	{
	  for (it = line.begin(); it != line.end(); it++)
	    {
	      if (*it == '1')
		_map[idx].push_back(std::shared_ptr<Map>(new Map(Arcade::CellType::WALL)));
	      else
		_map[idx].push_back(std::shared_ptr<Map>(new Map(Arcade::CellType::FREE)));
	    }
	  std::cout << line << std::endl;
	  ++idx;
	}
    }
}

Arcade::MapLoader::~MapLoader() {}
