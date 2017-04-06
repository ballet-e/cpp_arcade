//
// SolarFox.cpp for Arcade in /home/ballet/CPP/cpp_arcade/games/libsolarfox/SolarFox/
//
// Made by Ballet Erwan
// Login   <erwan.ballet@epitech.eu>
//
// Started on  Tue Apr  4 11:17:48 2017 Ballet Erwan
// Last update Thu Apr  6 21:29:03 2017 Erwan BALLET
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
  _end = false;
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
  Arcade::Bullet bullet1;
  Arcade::Bullet bullet2;
  Arcade::Bullet bullet3;
  Arcade::Bullet bullet4;
  
  _map.clear();
  Enemy1.setPos((MAP_WIDTH - 1) / 2, 0);
  bullet1.setPos(-1, -1);
  bullet1.setDir(Arcade::Bullet::UP);
  Enemy1.setBullet(bullet1);
  Enemy2.setPos((MAP_WIDTH - 1) / 2, MAP_HEIGHT - 1);
  bullet2.setPos(-1, -1);
  bullet2.setDir(Arcade::Bullet::DOWN);
  Enemy2.setBullet(bullet2);
  Enemy3.setPos(0, (MAP_HEIGHT - 1) / 2);
  bullet3.setPos(-1, -1);
  bullet3.setDir(Arcade::Bullet::RIGHT);
  Enemy3.setBullet(bullet3);
  Enemy4.setPos((MAP_WIDTH - 1), (MAP_HEIGHT - 1) / 2);
  bullet4.setPos(-1, -1);
  bullet4.setDir(Arcade::Bullet::LEFT);
  Enemy4.setBullet(bullet4);
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
      drawSquare(square_size, Arcade::Colors::AYELLOW,
		 _Enemy[i].getBullet().getPos().first * square_size,
		 _Enemy[i].getBullet().getPos().second * square_size);
      i += 1;
    }
  drawSquare(square_size, Arcade::Colors::AWHITE, _ship.first * square_size,
	     _ship.second * square_size);
}

void	Arcade::SolarFox::mooveEnemy(Arcade::Enemy En, int i)
{
  int	rd;

  if (_enemyMoove % 6 == 0)
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
	_enemyMoove = 1;
    }
  if (i == 3)
    _enemyMoove += 1;
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

int	Arcade::SolarFox::bulletEnd(Arcade::Bullet bullet)
{
  if ((bullet.getDir() == Arcade::Bullet::UP && bullet.getPos().second != MAP_HEIGHT - 2)
      || (bullet.getDir() == Arcade::Bullet::DOWN && bullet.getPos().second != 1)
      || (bullet.getDir() == Arcade::Bullet::LEFT && bullet.getPos().first != 1)
      || (bullet.getDir() == Arcade::Bullet::RIGHT
	  && bullet.getPos().first != MAP_WIDTH - 2))
    return 0;
  return 1;
}

void	Arcade::SolarFox::enemyShoot(int i)
{
  Arcade::Bullet	bullet;

  bullet = _Enemy[i].getBullet();
  if (bullet.getPos().first == -1)
    {
      if (_Enemy[i].getPos().first == 0)
	_Enemy[i].setBulletPos(1, _Enemy[i].getPos().second);
      else if (_Enemy[i].getPos().first == MAP_WIDTH - 1)
	_Enemy[i].setBulletPos(MAP_WIDTH - 2, _Enemy[i].getPos().second);
      else if (_Enemy[i].getPos().second == 0)
	_Enemy[i].setBulletPos(_Enemy[i].getPos().first , 1);
      else if (_Enemy[i].getPos().second == MAP_HEIGHT - 1)
	_Enemy[i].setBulletPos(_Enemy[i].getPos().first, MAP_HEIGHT - 2);
    }
  else if (bulletEnd(bullet) == 0)
    {
      if (bullet.getDir() == Arcade::Bullet::UP)
	_Enemy[i].setBulletPos(bullet.getPos().first, bullet.getPos().second + 1);
      else if (bullet.getDir() == Arcade::Bullet::DOWN)
	_Enemy[i].setBulletPos(bullet.getPos().first, bullet.getPos().second - 1);
      else if (bullet.getDir() == Arcade::Bullet::LEFT)
	_Enemy[i].setBulletPos(bullet.getPos().first - 1, bullet.getPos().second);
      else if (bullet.getDir() == Arcade::Bullet::RIGHT)
	_Enemy[i].setBulletPos(bullet.getPos().first + 1, bullet.getPos().second);
    }
  else
    {
      _Enemy[i].setBulletPos(-1, -1);
    }
}

void	Arcade::SolarFox::amIDead()
{
  int	i;

  i = 0;
  while (i < 4)
    {
      if (_ship.first == _Enemy[i].getBullet().getPos().first &&
	  _ship.second == _Enemy[i].getBullet().getPos().second)
	_end = true;
      i += 1;
    }
}

void	Arcade::SolarFox::render()
{
  int	i;
  
  i = 0;
  _validatePosition = true;
  if (!_isInit)
    initGame();
  amIDead();
  mooveShip();
  showMap();
  while (i < 4)
    {
      mooveEnemy(_Enemy[i], i);
      enemyShoot(i);
      i++;
    }
  if (_graderMode == false)
    {
      _graphic_library->setText(std::string("Niveau: ") + std::to_string(_score / 10), 10, Arcade::ElementPosition::LEFT);                                                                 
      _graphic_library->setText(std::string("SolarFox"), 10, Arcade::ElementPosition::CENTER, 25);
      _graphic_library->setText(std::string("Score: ") + std::to_string(_score), 10, Arcade::ElementPosition::RIGHT);
    }
  _dir = Arcade::Bullet::STOP;
  _frame = 1;
}

bool	Arcade::SolarFox::shouldRender()
{
  if (_frame % 5 == 0)
    return true;
  _frame += 1;
  return false;
}

Arcade::IGame::GameState	Arcade::SolarFox::gameState() const
{
  if (_end == true)
    return (Arcade::IGame::ENDED);
  return (Arcade::IGame::PLAYING);
}

unsigned int	Arcade::SolarFox::getMapWidth() const
{
  return (MAP_WIDTH);
}

unsigned int	Arcade::SolarFox::getMapHeight() const
{
  return (MAP_HEIGHT);
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
