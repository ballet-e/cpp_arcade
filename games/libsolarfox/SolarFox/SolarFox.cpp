//
// SolarFox.cpp for Arcade in /home/ballet/CPP/cpp_arcade/games/libsolarfox/SolarFox/
//
// Made by Ballet Erwan
// Login   <erwan.ballet@epitech.eu>
//
// Started on  Tue Apr  4 11:17:48 2017 Ballet Erwan
// Last update Thu Apr  6 00:20:09 2017 Erwan BALLET
//

#include <iostream>
#include <cstdlib>
#include "Bullet.hh"
#include "Enemy.hh"
#include "Protocol.hpp"
#include "SolarFox.hh"
#include "ScoreManager.hpp"
#include "IGraphic.hh"

Arcade::SolarFox::SolarFox() : _map(MAP_HEIGHT)
{
  _isInit = false;
  _graderMode = true;
  _frame = 0;
  _score = 0;
  _dir = Arcade::Bullet::STOP;
  _ship.first = MAP_WIDTH / 2;
  _ship.second = MAP_HEIGHT / 2;
  _pseudo = "Player";
}

Arcade::SolarFox::~SolarFox() {};

void	Arcade::SolarFox::setUpGraphics(Arcade::IGraphic *ref)
{
  _graderMode = false;
  _graphic_library = ref;
}

Arcade::LibraryType	Arcade::SolarFox::getLibraryType() const
{
  return (Arcade::GAME);
}

void			Arcade::SolarFox::setUpPseudo(std::string const& pseudo)
{
  _pseudo = pseudo;
}

void			Arcade::SolarFox::eventListener(Event const& e)
{
  if (!_validatePosition)
    return ;
  if (e.getType() == Arcade::Event::AKEY_UP)
    {
      _validatePosition = false;
      _dir = Arcade::Bullet::UP;
    }
  else if (e.getType() == Arcade::Event::AKEY_DOWN)
    {
      _validatePosition = false;
      _dir = Arcade::Bullet::DOWN;
    }
  else if (e.getType() == Arcade::Event::AKEY_LEFT)
    {
      _validatePosition = false;
      _dir = Arcade::Bullet::LEFT;
    }
  else if (e.getType() == Arcade::Event::AKEY_RIGHT)
    {
      _validatePosition = false;
      _dir = Arcade::Bullet::RIGHT;
    }
}

void	Arcade::SolarFox::initMap()
{
  unsigned int  x;
  unsigned int  y;

  y = 0;
  while (y < MAP_HEIGHT)
    {
      x = 0;
      while (x < MAP_WIDTH)
        {
          if (x == 0 || x + 1 == MAP_WIDTH || y == 0 || y + 1 == MAP_HEIGHT)
            _map[y].push_back(1);
          else
            _map[y].push_back(0);
          ++x;
        }
      ++y;
    }
}

void	Arcade::SolarFox::initGame()
{
  Arcade::Enemy	Enemy1;
  Arcade::Enemy	Enemy2;
  Arcade::Enemy	Enemy3;
  Arcade::Enemy	Enemy4;
  
  _map.clear();
  Enemy1.setPos((MAP_HEIGHT - 1) / 2, 0);
  Enemy2.setPos((MAP_HEIGHT - 1) / 2, MAP_WIDTH - 1);
  Enemy3.setPos(0, (MAP_WIDTH - 1) / 2);
  Enemy4.setPos((MAP_HEIGHT - 1), (MAP_WIDTH - 1) / 2);
  this->_Enemy[0] = Enemy1;
  this->_Enemy[1] = Enemy2;
  this->_Enemy[2] = Enemy3;
  this->_Enemy[3] = Enemy4;
  initMap();
  _isInit = true;
  _validatePosition = true;
  _end = false;
}

void	Arcade::SolarFox::drawSquare(unsigned int size, unsigned int color,
				     unsigned int pos_x, unsigned int pos_y)
{
  unsigned int  x;
  unsigned int  y;

  y = 0;
  while (y < size)
    {
      x = 0;
      while (x < size)
        {
          if (size != 1 && (y == 0 || y + 1 == size || x == 0 || x + 1 == size))
            _graphic_library->setPixel(pos_x + x, pos_y + y, 0);
          else
            _graphic_library->setPixel(pos_x + x, pos_y + y, color);
          ++x;
        }
      ++y;
    }
}


void	Arcade::SolarFox::showMap()
{
  unsigned int	i;
  unsigned int  x;
  unsigned int  y;
  unsigned int  square_size;

  square_size = _graphic_library->getDrawableHeight() / MAP_HEIGHT;
  y = 0;
  while (y < MAP_HEIGHT)
    {
      x = 0;
      while (x < MAP_WIDTH)
	{
          if (_map[y][x] == 0)
            drawSquare(square_size, Arcade::Colors::ABLACK, x * square_size, y * square_size);
          else if (_map[y][x] == 1)
            drawSquare(square_size, Arcade::Colors::AGREY, x * square_size, y * square_size);
          ++x;
	}
      ++y;
    }
  i = 0;
  while (i < 4)
    {
      drawSquare(square_size, Arcade::Colors::ARED, _Enemy[i].getPos().first * square_size,
		 _Enemy[i].getPos().second * square_size);
      i += 1;
    }
  drawSquare(square_size, Arcade::Colors::AWHITE, _ship.first * square_size,
	     _ship.second * square_size);
}

void	Arcade::SolarFox::mooveEnemy(Arcade::Enemy En, int i)
{
  int	rd;

  if (_frame % 6 == 0)
    {
      rd = rand() % 2;
      if (En.getPos().first == 0 || En.getPos().first == 19)
	{
	  if (En.getPos().second == 1)
	    _Enemy[i].setPos(En.getPos().first, En.getPos().second + 1);
	  else if (En.getPos().second == 18)
	    _Enemy[i].setPos(En.getPos().first, En.getPos().second - 1);
	  else if (rd == 0)
	    _Enemy[i].setPos(En.getPos().first, En.getPos().second + 1);
	  else
	    _Enemy[i].setPos(En.getPos().first, En.getPos().second - 1);
	}
      else
	{
	  if (En.getPos().first == 1)
	    _Enemy[i].setPos(En.getPos().first + 1, En.getPos().second);
	  else if (En.getPos().first == 18)
	    _Enemy[i].setPos(En.getPos().first - 1, En.getPos().second);
	  else if (rd == 0)
	    _Enemy[i].setPos(En.getPos().first - 1, En.getPos().second);
	  else
	    _Enemy[i].setPos(En.getPos().first + 1, En.getPos().second);
	}
      if (i == 3)
	_frame = 1;
    }
  if (i == 3)
    _frame += 1;
}

void	Arcade::SolarFox::mooveShip()
{
  if (_dir == Arcade::Bullet::UP && _ship.second > 1)
    _ship.second -= 1;
  if (_dir == Arcade::Bullet::DOWN && _ship.second < 18)
    _ship.second += 1;
  if (_dir == Arcade::Bullet::LEFT && _ship.first > 1)
    _ship.first -= 1;
  if (_dir == Arcade::Bullet::RIGHT && _ship.first < 18)
    _ship.first += 1;
}

void	Arcade::SolarFox::render()
{
  int	i;
  
  i = 0;
  mooveShip();
  _validatePosition = true;
  if (!_isInit)
    initGame();
  showMap();
  while (i < 4)
    {
      mooveEnemy(_Enemy[i], i);
      i++;
    }
  if (_graderMode == false)
    {
      _graphic_library->setText(std::string("Niveau: ") + std::to_string(_score / 10), 10, Arcade::ElementPosition::LEFT);                                                                 
      _graphic_library->setText(std::string("SolarFox"), 10, Arcade::ElementPosition::CENTER, 25);
      _graphic_library->setText(std::string("Score: ") + std::to_string(_score), 10, Arcade::ElementPosition::RIGHT);
    }
  _dir = Arcade::Bullet::STOP;
  /*if (_playing)
    moveSolarFox(); */
}

bool	Arcade::SolarFox::shouldRender()
{
  return true;
}

Arcade::IGame::GameState	Arcade::SolarFox::gameState() const
{
  return (Arcade::IGame::PLAYING);
}

void	Arcade::SolarFox::whereAmI() {}

void	Arcade::SolarFox::getMap() {}

void	Arcade::SolarFox::goUp() {}

void	Arcade::SolarFox::goDown() {}

void	Arcade::SolarFox::goLeft() {}

void	Arcade::SolarFox::goRight() {}

void	Arcade::SolarFox::goForward() {}

void	Arcade::SolarFox::makeShoot() {}

void	Arcade::SolarFox::illegal() {}

void	Arcade::SolarFox::playRound() {}
