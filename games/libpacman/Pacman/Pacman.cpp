//
// Pacman.cpp for cpp_arcade in /home/wurmel_a/rendu/cpp_arcade/games/libpacman
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sun Apr  9 15:51:30 2017 Arnaud WURMEL
// Last update Sun Apr  9 18:48:31 2017 Arnaud WURMEL
//

#include <iostream>
#include <map>
#include <utility>
#include "Pacman.hh"

Arcade::Pacman::Pacman()
{
  _graphic_library = NULL;
  _graderMode = true;
  initGame();
}

void	Arcade::Pacman::setUpGraphics(Arcade::IGraphic *graphic)
{
  _graderMode = false;
  _graphic_library = graphic;
}

void	Arcade::Pacman::setUpPseudo(std::string const& pseudo)
{
  _pseudo = pseudo;
}

Arcade::LibraryType	Arcade::Pacman::getLibraryType() const
{
  return Arcade::LibraryType::GAME;
}

void	Arcade::Pacman::eventListener(Arcade::Event const& e)
{
  std::map<Arcade::Event::EventType, Arcade::Pacman::Direction>	map;
  std::map<Arcade::Event::EventType, std::function<bool ()>>	checker;

  map.insert(std::make_pair(Arcade::Event::EventType::AKEY_UP, Arcade::Pacman::Up));
  map.insert(std::make_pair(Arcade::Event::EventType::AKEY_DOWN, Arcade::Pacman::Down));
  map.insert(std::make_pair(Arcade::Event::EventType::AKEY_LEFT, Arcade::Pacman::Left));
  map.insert(std::make_pair(Arcade::Event::EventType::AKEY_RIGHT, Arcade::Pacman::Right));
  checker.insert(std::make_pair(Arcade::Event::EventType::AKEY_UP, std::bind(&Arcade::Pacman::canUp, this)));
  checker.insert(std::make_pair(Arcade::Event::EventType::AKEY_DOWN, std::bind(&Arcade::Pacman::canDown, this)));
  checker.insert(std::make_pair(Arcade::Event::EventType::AKEY_LEFT, std::bind(&Arcade::Pacman::canLeft, this)));
  checker.insert(std::make_pair(Arcade::Event::EventType::AKEY_RIGHT, std::bind(&Arcade::Pacman::canRight, this)));
  if (map.find(e.getType()) != map.end())
    {
      if (checker[e.getType()]())
	{
	  _dir = map[e.getType()];
	  _validate = Arcade::Pacman::Direction::None;
	}
      else
	_validate = map[e.getType()];
    }
}

void	Arcade::Pacman::drawSquare(unsigned int x,
				   unsigned int y,
				   unsigned int size,
				   Arcade::Colors const& color)
{
  Arcade::Position	idx;

  idx.y = 0;
  while (idx.y < size)
    {
      idx.x = 0;
      while (idx.x < size)
	{
	  _graphic_library->setPixel(x + idx.x, y + idx.y, color);
	  ++idx.x;
	}
      ++idx.y;
    }
}

void	Arcade::Pacman::render()
{
  std::map<Arcade::CellType, Arcade::Colors>	colors;
  Arcade::Colors	color;
  Arcade::Position	idx;
  unsigned int	size;

  colors.insert(std::make_pair(Arcade::CellType::FREE, Arcade::Colors::AGREY));
  colors.insert(std::make_pair(Arcade::CellType::WALL, Arcade::Colors::ABLACK));
  colors.insert(std::make_pair(Arcade::CellType::EAT, Arcade::Colors::ACYAN));
  colors.insert(std::make_pair(Arcade::CellType::POWER_UP, Arcade::Colors::AGREEN));
  if (_end)
    return ;
  moveP();
  size = (_graphic_library->getDrawableWidth() / _width);
  idx.y = 0;
  while (idx.y < _height)
    {
      idx.x = 0;
      while (idx.x < _width)
	{
	  color = Arcade::Colors::ABLACK;
	  if (colors.find(_map[idx.x + (idx.y * _width)]->_type) != colors.end())
	    color = colors[_map[idx.x + (idx.y * _width)]->_type];
	  drawSquare(idx.x * size, idx.y * size, size, color);
	  ++idx.x;
	}
      ++idx.y;
    }
  drawSquare(_p.x * size, _p.y * size, size, Arcade::Colors::AYELLOW);
}

void	Arcade::Pacman::moveP()
{
  std::map<Arcade::Pacman::Direction, std::function<void ()>>	binding;
  std::map<Arcade::Pacman::Direction, std::function<bool ()>>	checker;

  binding.insert(std::make_pair(Arcade::Pacman::Up, std::bind(&Arcade::Pacman::goUp, this)));
  binding.insert(std::make_pair(Arcade::Pacman::Down, std::bind(&Arcade::Pacman::goDown, this)));
  binding.insert(std::make_pair(Arcade::Pacman::Right, std::bind(&Arcade::Pacman::goRight, this)));
  binding.insert(std::make_pair(Arcade::Pacman::Left, std::bind(&Arcade::Pacman::goLeft, this)));
  checker.insert(std::make_pair(Arcade::Pacman::Up, std::bind(&Arcade::Pacman::canUp, this)));
  checker.insert(std::make_pair(Arcade::Pacman::Down, std::bind(&Arcade::Pacman::canDown, this)));
  checker.insert(std::make_pair(Arcade::Pacman::Left, std::bind(&Arcade::Pacman::canLeft, this)));
  checker.insert(std::make_pair(Arcade::Pacman::Right, std::bind(&Arcade::Pacman::canRight, this)));
  if (_validate != Arcade::Pacman::None)
    {
      if (checker[_validate]())
	{
	  _dir = _validate;
	  _validate = Arcade::Pacman::None;
	}
    }
  if (binding.find(_dir) != binding.end())
    {
      binding[_dir]();
      eat();
    }
}

void	Arcade::Pacman::eat()
{
  if (_map[_p.x + (_p.y * _width)]->_type == Arcade::CellType::EAT)
    {
      _map[_p.x + (_p.y * _width)]->_type = Arcade::CellType::FREE;
      _score += 10;
    }
}

bool	Arcade::Pacman::shouldRender()
{
  if (_frame % 10 == 0)
    {
      _frame = 1;
      return true;
    }
  _frame += 1;
  return false;
}

void	Arcade::Pacman::initGame()
{
  _end = false;
  _map = _loader.getMap("Ressources/pacman/map.pacman");
  if (_map.size() == 0)
    {
      _end = true;
      return ;
    }
  _dir = Arcade::Pacman::Direction::None;
  _validate = Arcade::Pacman::Direction::None;
  _p = _loader.getPlayerPosition();
  _width = _loader.getMapWidth();
  _height = _loader.getMapHeight();
  _frame = 0;
  _score = 0;
}

unsigned int	Arcade::Pacman::getMapWidth() const
{
  return _width;
}

unsigned int	Arcade::Pacman::getMapHeight() const
{
  return _height;
}

Arcade::IGame::GameState	Arcade::Pacman::gameState() const
{
  return (Arcade::IGame::PLAYING);
}

void	Arcade::Pacman::goUp()
{
  if (canUp())
    _p.y -= 1;
  else if (_p.y == 0 && _map[_p.x + ((_height - 1) * _width)]->_type != Arcade::CellType::WALL)
    {
      _p.y = _height - 1;
    }
}

void	Arcade::Pacman::goDown()
{
  if (canDown())
    {
      _p.y += 1;
    }
  else if (_p.y == _height - 1 && _map[_p.x]->_type != Arcade::CellType::WALL)
    {
      _p.y = 0;
    }
}

void	Arcade::Pacman::goLeft()
{
  if (canLeft())
    _p.x -= 1;
  else if (_p.x == 0 && _map[(_width - 1) + (_p.y * _width)]->_type != Arcade::CellType::WALL)
    {
      _p.x = _width - 1;
    }
}

void	Arcade::Pacman::goRight()
{
  if (canRight())
    _p.x += 1;
  else if (_p.x == _width - 1 && _map[_p.y * _width]->_type != Arcade::CellType::WALL)
    {
      _p.x = 0;
    }
}

bool	Arcade::Pacman::canLeft() const
{
  if (_p.x > 0 && _map[(_p.x - 1) + (_p.y * _width)]->_type != Arcade::CellType::WALL)
    return true;
  return false;
}

bool	Arcade::Pacman::canRight() const
{
  if (_p.x + 1 < _width && _map[(_p.x + 1) + (_p.y * _width)]->_type != Arcade::CellType::WALL)
    return true;
  return false;
}

bool	Arcade::Pacman::canUp() const
{
  if (_p.y > 0 && _map[_p.x + ((_p.y - 1) * _width)]->_type != Arcade::CellType::WALL)
    return true;
  return false;
}

bool	Arcade::Pacman::canDown() const
{
  if (_p.y + 1 < _height && _map[_p.x + ((_p.y + 1) * _width)]->_type != Arcade::CellType::WALL)
    return true;
  return false;
}

Arcade::Pacman::~Pacman()
{
  _map.clear();
}
