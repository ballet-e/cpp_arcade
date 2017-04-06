//
// MapLoader.cpp for cpp_arcade in /home/wurmel_a/rendu/cpp_arcade/games/libwolf3d
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Thu Apr  6 18:29:28 2017 Arnaud WURMEL
// Last update Thu Apr  6 19:13:54 2017 Arnaud WURMEL
//

#include "MapLoader.hh"

Arcade::MapLoader::MapLoader()
{

}

std::vector<std::unique_ptr<Arcade::Map>> const&	Arcade::MapLoader::getMap()
{
  if (_map.size() > 0)
    return _map;
  loadFile();
  return _map;
}

void	Arcade::MapLoader::loadFile()
{
  
}

Arcade::MapLoader::~MapLoader() {}
