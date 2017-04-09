//
// MapLoader.cpp for cpp_arcade in /home/wurmel_a/rendu/cpp_arcade/games/libwolf3d
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Thu Apr  6 18:29:28 2017 Arnaud WURMEL
// Last update Sun Apr  9 18:29:45 2017 Arnaud WURMEL
//

#include <iostream>
#include <map>
#include <utility>
#include <fstream>
#include "MapLoader.hh"

Arcade::MapLoader::MapLoader()
{

}

std::vector<std::shared_ptr<Arcade::Map>> const&	Arcade::MapLoader::getMap(std::string const& file_path)
{
  if (_map.size() > 0)
    return _map;
  _width = 0;
  _height = 0;
  loadFile(file_path);
  if (foundPosition() == false)
    _map.clear();
  return _map;
}

void	Arcade::MapLoader::deleteMap()
{
  _map.clear();
}

bool	Arcade::MapLoader::foundPosition()
{
  _p.y = 0;
  while (_p.y < _height)
    {
      _p.x = 0;
      while (_p.x < _width)
	{
	  if (_p.x + (_p.y * _width) < _width * _height)
	    {
	      if (_map[_p.x + (_p.y * _width)]->_type == PLAYER)
		{
		  _map[_p.x + (_p.y * _width)]->_type = FREE;
		  return true;
		}
	    }
	  ++_p.x;
	}
      ++_p.y;
    }
  return false;
}

Arcade::Position const&	Arcade::MapLoader::getPlayerPosition() const
{
  return _p;
}

unsigned int	Arcade::MapLoader::getMapWidth() const
{
  return _width;
}

unsigned int	Arcade::MapLoader::getMapHeight() const
{
  return _height;
}

void	Arcade::MapLoader::loadFile(std::string const& file_path)
{
  std::string	line;
  std::ifstream	f;
  std::string::iterator	it;
  std::map<int, Arcade::CellType>	cell_type;

  cell_type.insert(std::make_pair('0', Arcade::CellType::FREE));
  cell_type.insert(std::make_pair('1', Arcade::CellType::WALL));
  cell_type.insert(std::make_pair('2', Arcade::CellType::PLAYER));
  cell_type.insert(std::make_pair('3', Arcade::CellType::EAT));
  cell_type.insert(std::make_pair('4', Arcade::CellType::POWER_UP));
  _map.clear();
  f.open(file_path);
  if (f.is_open())
    {
      while (std::getline(f, line))
	{
	  if (_width == 0)
	    _width = line.size();
	  else if (_width != line.size())
	    return ;
	  for (it = line.begin(); it != line.end(); it++)
	    {
	      if (cell_type.find((*it)) != cell_type.end())
		_map.push_back(std::shared_ptr<Map>(new Map(cell_type[(*it)])));
	    }
	  _height += 1;
	}
    }
}

Arcade::MapLoader::~MapLoader() {}
