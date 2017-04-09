//
// IA.cpp for  in /home/ballet_e/CPP/cpp_arcade/games/libpacman/Pacman
// 
// Made by Erwan BALLET
// Login   <ballet_e@epitech.net>
// 
// Started on  Sun Apr  9 14:20:11 2017 Erwan BALLET
// Last update Sun Apr  9 18:57:05 2017 Erwan BALLET
//

#include "IA.hh"

Arcade::IA::IA() : _state(Arcade::IA::LIVE)
{
  _pos.first = 0;
  _pos.second = 0;
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
  if (state == Arcade::IA::AFRAID)
    _dir = (this->*_changeDir[_dir])();
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

bool				Arcade::IA::checkUp(std::vector<std::shared_ptr<Arcade::Map>> map, unsigned int height, unsigned int width)
{
  static_cast<void>(height);
  if ((_pos.first >= 1 && map[_pos.first + _pos.second * width]->_type != WALL)
      || (_pos.first + 1 < width && map[_pos.first + _pos.second * width]->_type != WALL))
    return (true);
  else
    return (false);
}

bool				Arcade::IA::checkDown(std::vector<std::shared_ptr<Arcade::Map>> map, unsigned int height, unsigned int width)
{
  static_cast<void>(height);
  if ((_pos.first >= 1 && map[_pos.first + _pos.second * width]->_type != WALL)
      || (_pos.first + 1 < width && map[_pos.first + _pos.second * width]->_type != WALL))
    return (true);
  else
    return (false);
}

bool				Arcade::IA::checkLeft(std::vector<std::shared_ptr<Arcade::Map>> map, unsigned int height, unsigned int width)
{
  if ((_pos.second >= 1 && map[_pos.first + _pos.second * width]->_type != WALL)
      || (_pos.second + 1 < height && map[_pos.first + _pos.second * width]->_type != WALL))
    return (true);
  else
    return (false);
}

bool				Arcade::IA::checkRight(std::vector<std::shared_ptr<Arcade::Map>> map, unsigned int height, unsigned int width)
{
  if ((_pos.second >= 1 && map[_pos.first + _pos.second * width]->_type != WALL)
      || (_pos.second + 1 < height && map[_pos.first + _pos.second * width]->_type != WALL))
    return (true);
  else
    return (false);
}

void				Arcade::IA::mooveIA(std::vector<std::shared_ptr<Arcade::Map>> map, unsigned int height, unsigned int width)
{
  std::pair<unsigned int, unsigned int>			newPos;
  std::vector<Arcade::IA::Directions>	allDir;
  bool					stayIn;
  int					rd;

  if (_pos.first != 0 || _inc[_dir].first >= 0)
    newPos.first = _pos.first + _inc[_dir].first;
  if (_pos.second != 0 || _inc[_dir].second >= 0)
    newPos.second = _pos.second + _inc[_dir].second;
  allDir.push_back(Arcade::IA::UP);
  allDir.push_back(Arcade::IA::DOWN);
  allDir.push_back(Arcade::IA::LEFT);
  allDir.push_back(Arcade::IA::RIGHT);
  if ((this->*_findWay[_dir])(map, height, width))
    {
      stayIn = true;
      while (stayIn)
	{
	  rd = std::rand() % allDir.size();
	  if (_pos.first != 0 || _inc[allDir[rd]].first >= 0)
	    newPos.first = _pos.first + _inc[allDir[rd]].first;
	  if (_pos.second != 0 || _inc[allDir[rd]].second >= 0)
	    newPos.first = _pos.second + _inc[allDir[rd]].second;
	  if (newPos.first < width && newPos.second < height
	      && map[newPos.first + newPos.second * width]->_type != WALL)
	    stayIn = false;
	  else
	    allDir.erase(allDir.begin() + rd);
	}
      if (allDir.size() > 0)
	{
	  _dir = allDir[rd];
	  _pos = newPos;
	}
    }
  else if ((this->*_findWay[_dir])(map, height, width) == false
	   && newPos.first < width && newPos.second <= height
	   && map[newPos.first + newPos.second * width]->_type == WALL)
    _dir = (this->*_changeDir[_dir])();
  else
    _pos = newPos;
}
