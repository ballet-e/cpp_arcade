//
// IA.cpp for  in /home/ballet_e/CPP/cpp_arcade/games/libpacman/Pacman
// 
// Made by Erwan BALLET
// Login   <ballet_e@epitech.net>
// 
// Started on  Sun Apr  9 14:20:11 2017 Erwan BALLET
// Last update Sun Apr  9 21:28:10 2017 Erwan BALLET
//

#include <iostream>
#include "IA.hh"

Arcade::IA::IA(unsigned int x, unsigned int y) : _state(Arcade::IA::LIVE)
{
  _pos.first = x;
  _pos.second = y;
  _dir = Arcade::IA::UP;
  _changeDir[Arcade::IA::UP] = &Arcade::IA::invUp;
  _changeDir[Arcade::IA::DOWN] = &Arcade::IA::invDown;
  _changeDir[Arcade::IA::LEFT] = &Arcade::IA::invLeft;
  _changeDir[Arcade::IA::RIGHT] = &Arcade::IA::invRight;
  _inc[Arcade::IA::UP].first = 0;
  _inc[Arcade::IA::UP].second = -1;
  _inc[Arcade::IA::DOWN].first = 0;
  _inc[Arcade::IA::DOWN].second = 1;
  _inc[Arcade::IA::LEFT].first = -1;
  _inc[Arcade::IA::LEFT].second = 0;
  _inc[Arcade::IA::RIGHT].first = 1;
  _inc[Arcade::IA::RIGHT].second = 0;
  _findWay[Arcade::IA::UP] = &Arcade::IA::checkUp;
  _findWay[Arcade::IA::DOWN] = &Arcade::IA::checkDown;
  _findWay[Arcade::IA::LEFT] = &Arcade::IA::checkLeft;
  _findWay[Arcade::IA::RIGHT] = &Arcade::IA::checkRight;
}

Arcade::IA::~IA() {}

const Arcade::IA::State&	Arcade::IA::getState() const
{
  return (_state);
}

void		Arcade::IA::setState(const Arcade::IA::State& state)
{
  _state = state;
  if (state == Arcade::IA::AFRAID || state == Arcade::IA::DEAD)
    _isState = 60;
}

std::pair<int, int>		Arcade::IA::getPos() const
{
  return (_pos);
}

void				Arcade::IA::setPos(int x, int y)
{
  _pos.first = x;
  _pos.second = y;
}

Arcade::IA::Directions		Arcade::IA::invUp()
{
  return (Arcade::IA::DOWN);
}

Arcade::IA::Directions		Arcade::IA::invDown()
{
  return (Arcade::IA::DOWN);
}

Arcade::IA::Directions		Arcade::IA::invLeft()
{
  return (Arcade::IA::DOWN);
}

Arcade::IA::Directions		Arcade::IA::invRight()
{
  return (Arcade::IA::DOWN);
}

bool				Arcade::IA::checkDown(std::vector<std::shared_ptr<Arcade::Map>> map, unsigned int height, unsigned int width)
{
  static_cast<void>(height);
  if (_pos.first == 0 && map[_pos.first + (_pos.second + 1) * width]->_type == Arcade::CellType::WALL)
    return (false);
  if (map[_pos.first - 1 + _pos.second * width]->_type != Arcade::CellType::WALL
      || (_pos.first + 1 < width && map[_pos.first + 1 + _pos.second * width]->_type != Arcade::CellType::WALL))
    return (true);
  else
    return (false);
}

bool				Arcade::IA::checkUp(std::vector<std::shared_ptr<Arcade::Map>> map, unsigned int height, unsigned int width)
{
  static_cast<void>(height);
  if (_pos.first == 0 && map[_pos.first + (_pos.second - 1) * width]->_type == Arcade::CellType::WALL)
    return (false);
  if (map[_pos.first - 1 + _pos.second * width]->_type != Arcade::CellType::WALL
      || (_pos.first + 1 < width && map[_pos.first + 1 + _pos.second * width]->_type != Arcade::CellType::WALL))
    return (true);
  else
    return (false);
}

bool				Arcade::IA::checkLeft(std::vector<std::shared_ptr<Arcade::Map>> map, unsigned int height, unsigned int width)
{
  if (_pos.second == 0 && map[_pos.first - 1 + _pos.second * width]->_type == Arcade::CellType::WALL)
    return (false);
  if (map[_pos.first + (_pos.second - 1) * width]->_type != WALL
      || (_pos.second + 1 < height && map[_pos.first + (_pos.second + 1) * width]->_type != Arcade::CellType::WALL))
    return (true);
  else
    return (false);
}

bool				Arcade::IA::checkRight(std::vector<std::shared_ptr<Arcade::Map>> map, unsigned int height, unsigned int width)
{
  if (_pos.second == 0 && map[_pos.first -1 + _pos.second * width]->_type == Arcade::CellType::WALL)
    return (false);
  if (map[_pos.first + (_pos.second - 1) * width]->_type != WALL
      || (_pos.second + 1 < height && map[_pos.first + (_pos.second + 1) * width]->_type != Arcade::CellType::WALL))
    return (true);
  else
    return (false);
}

void				Arcade::IA::mooveIA(std::vector<std::shared_ptr<Arcade::Map>> map, unsigned int height, unsigned int width)
{
  std::vector<Arcade::IA::Directions>	allDir;
  bool					stayIn;
  int					rd;

  if (_state == Arcade::IA::DEAD)
    {
      if (_isState > 0)
	_isState -= 1;
      else
	_state = Arcade::IA::LIVE;
    }
  else
    {
      if (_state == Arcade::IA::AFRAID)
	{
	  if (_isState > 0)
	    _isState -= 1;
	  else
	    _state = Arcade::IA::LIVE;
	}
      allDir.push_back(Arcade::IA::UP);
      allDir.push_back(Arcade::IA::DOWN);
      allDir.push_back(Arcade::IA::LEFT);
      allDir.push_back(Arcade::IA::RIGHT);
      stayIn = true;
      while (allDir.size() > 0 && stayIn)
	{
	  rd = std::rand() % allDir.size();
	  unsigned int idx = (_pos.first + _inc[allDir[rd]].first) + ((_pos.second + _inc[allDir[rd]].second) * width);
	  if (_pos.first + _inc[allDir[rd]].first < width
	      && _pos.second + _inc[allDir[rd]].second < height
	      && map[idx]->_type != Arcade::CellType::WALL)
	    {
	      stayIn = false;
	      _dir = allDir[rd];
	      _pos.first += _inc[allDir[rd]].first;
	      _pos.second += _inc[allDir[rd]].second;
	    }
	  else
	    allDir.erase(allDir.begin() + rd);
	}
    }
}
