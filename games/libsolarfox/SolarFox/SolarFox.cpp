//
// SolarFox.cpp for Arcade in /home/ballet/CPP/cpp_arcade/games/libsolarfox/SolarFox/
//
// Made by Ballet Erwan
// Login   <erwan.ballet@epitech.eu>
//
// Started on  Tue Apr  4 11:17:48 2017 Ballet Erwan
// Last update Sun Apr  9 13:19:17 2017 Erwan BALLET
//

#include <iostream>
#include <cstdlib>
#include <string.h>
#include <map>
#include "Bullet.hh"
#include "Enemy.hh"
#include "Protocol.hpp"
#include "SolarFox.hh"
#include "ScoreManager.hpp"
#include "IGraphic.hh"

Arcade::SolarFox::SolarFox() : _map(MAP_HEIGHT)
{
  _incDir[Arcade::Bullet::UP] = &Arcade::SolarFox::incUp;
  _incDir[Arcade::Bullet::DOWN] = &Arcade::SolarFox::incDown;
  _incDir[Arcade::Bullet::LEFT] = &Arcade::SolarFox::incLeft;
  _incDir[Arcade::Bullet::RIGHT] = &Arcade::SolarFox::incRight;
  _isInit = false;
  _points = false;
  _shouldMoove = 0;
  _graderMode = true;
  _frame = 0;
  _lv = 1;
  _travel = 0;
  _myShoot.setPos(MAP_WIDTH / 2, MAP_HEIGHT / 2);
  _myShoot.setDir(Arcade::Bullet::LEFT);
  _score = 0;
  _end = false;
  _scoreSet = false;
  _dir = Arcade::Bullet::LEFT;
  _ship.first = MAP_WIDTH / 2;
  _ship.second = MAP_HEIGHT / 2;
  _pseudo = "Player";
  initGame();
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

void			Arcade::SolarFox::saveScore() const
{
  Arcade::ScoreManager	scoreManager;

  scoreManager.addScoreForGame("solar_fox", _pseudo, _score);
}

void			Arcade::SolarFox::eventListener(Event const& e)
{
  if (!_validatePosition)
    return ;
  if (e.getType() == Arcade::Event::AKEY_UP && _dir != Arcade::Bullet::DOWN)
    {
      _validatePosition = false;
      _dir = Arcade::Bullet::UP;
    }
  else if (e.getType() == Arcade::Event::AKEY_DOWN && _dir != Arcade::Bullet::UP)
    {
      _validatePosition = false;
      _dir = Arcade::Bullet::DOWN;
    }
  else if (e.getType() == Arcade::Event::AKEY_LEFT && _dir != Arcade::Bullet::RIGHT)
    {
      _validatePosition = false;
      _dir = Arcade::Bullet::LEFT;
    }
  else if (e.getType() == Arcade::Event::AKEY_RIGHT && _dir != Arcade::Bullet::LEFT)
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

  _frame = 0;
  _score = 0;
  _end = false;
  _ship.first = MAP_WIDTH / 2;
  _ship.second = MAP_HEIGHT / 2;
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
  while (i < _pointTab.size())
    {
      drawSquare(square_size, Arcade::Colors::ACYAN, _pointTab[i].first * square_size,
		 _pointTab[i].second * square_size);
      i += 1;
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
  drawSquare(square_size, Arcade::Colors::AGREEN, _myShoot.getPos().first * square_size,
	     _myShoot.getPos().second * square_size);
  drawSquare(square_size, Arcade::Colors::AWHITE, _ship.first * square_size,
	     _ship.second * square_size);
}

void	Arcade::SolarFox::mooveEnemy(Arcade::Enemy En, int i)
{
  int	rd;

  if (_enemyMoove % 2 == 0)
    {
      rd = std::rand() % 2;
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
  else if (_dir == Arcade::Bullet::UP && _ship.second <= 1)
    _end = true;
  if (_dir == Arcade::Bullet::DOWN && _ship.second < 18)
    _ship.second += 1;
  else if (_dir == Arcade::Bullet::DOWN && _ship.second >= 18)
    _end = true;
  if (_dir == Arcade::Bullet::LEFT && _ship.first > 1)
    _ship.first -= 1;
  else if (_dir == Arcade::Bullet::LEFT && _ship.first <= 1)
    _end = true;
  if (_dir == Arcade::Bullet::RIGHT && _ship.first < 18)
    _ship.first += 1;
  else if (_dir == Arcade::Bullet::RIGHT && _ship.first >= 18)
    _end = true;
}

int	Arcade::SolarFox::bulletEnd(Arcade::Bullet bullet)
{
  if ((bullet.getDir() == Arcade::Bullet::UP && bullet.getPos().second != MAP_HEIGHT - 2)
      || (bullet.getDir() == Arcade::Bullet::DOWN && bullet.getPos().second != 1)
      || (bullet.getDir() == Arcade::Bullet::LEFT && bullet.getPos().first != 1)
      || (bullet.getDir() == Arcade::Bullet::RIGHT
	  && bullet.getPos().first != MAP_WIDTH - 2))
    return 0;
  if (bullet.getPos().first == _myShoot.getPos().first
      && bullet.getPos().second == _myShoot.getPos().second)
    return 1;
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
  if (_end == true && _scoreSet == false)
    {
      _scoreSet = true;
      saveScore();
    }
}

void	Arcade::SolarFox::setPoints()
{
  std::vector<std::pair<unsigned int, unsigned int>>	points;
  std::pair<int, int>					pos;
  int							i;

  pos.second = 2;
  while (pos.second < MAP_HEIGHT - 3)
    {
      pos.first = 2;
      while (pos.first < MAP_WIDTH - 3)
	{
	  if (pos.first != _ship.first && pos.second != _ship.second)
	    points.push_back(pos);
	  pos.first += 1;
	}
      pos.second += 1;
    }
  i = 0;
  while (i < 20)
    {
      pos.first = std::rand() % points.size();
      _pointTab.push_back(points[pos.first]);
      points.erase(points.begin() + pos.first);
      i += 1;
    }
  _points = true;
}

void		Arcade::SolarFox::didIGetPoints()
{
  if (_pointTab.size() == 0)
    {
      _score += 10000;
      _lv += 1;
      _ship.first = MAP_WIDTH / 2;
      _ship.second = MAP_HEIGHT / 2;
      _dir = Arcade::Bullet::LEFT;
      _points = false;
      return ;
    }
}

void	Arcade::SolarFox::mooveMyShoot()
{
  std::pair<int, int>	pos;
  unsigned int		i;

  i = 0;
  if (_travel == 2)
    {
      pos = (this->*_incDir[_dir])(_ship);
      _myShoot.setPos(pos.first, pos.second);
      _myShoot.setDir(_dir);
      _travel = 0;
    }
  else
    {
      pos = (this->*_incDir[_myShoot.getDir()])(_myShoot.getPos());
      _myShoot.setPos(pos.first, pos.second);
      _travel += 1;
    }
  while (i < _pointTab.size())
    {
      if (_pointTab[i].first == _myShoot.getPos().first &&
	  _pointTab[i].second == _myShoot.getPos().second)
	{
	  _score += 1000;
	  _pointTab.erase(_pointTab.begin() + i);
	  return ;
	}
      i += 1;
    }
  i = 0;
  while (i < 4)
    {
      if (_Enemy[i].getBullet().getPos().first == _myShoot.getPos().first &&
	  _Enemy[i].getBullet().getPos().second == _myShoot.getPos().second)
	_Enemy[i].setBulletPos(-1, -1);
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
  if (!_points)
    setPoints();
  mooveMyShoot();
  if (_shouldMoove % 3 == 0)
    {
      amIDead();
      didIGetPoints();
      mooveShip();
      amIDead();
      while (i < 4)
	{
	  mooveEnemy(_Enemy[i], i);
	  enemyShoot(i);
	  i++;
	}
    }
  if (_graderMode == false)
    {
      showMap();
      _graphic_library->setText(std::string("Niveau: ") + std::to_string(_lv), 10, Arcade::ElementPosition::LEFT);                                                                 
      _graphic_library->setText(std::string("SolarFox"), 10, Arcade::ElementPosition::CENTER, 25);
      _graphic_library->setText(std::string("Score: ") + std::to_string(_score), 10, Arcade::ElementPosition::RIGHT);
    }
  _shouldMoove += 1;
  _frame = 1;
}

bool	Arcade::SolarFox::shouldRender()
{
  if (_frame % 3 == 0)
    return true;
  _frame += 1;
  return false;
}

std::pair<int, int>	Arcade::SolarFox::incUp(std::pair<int, int> pos)
{
  if (pos.second > 1)
    pos.second -= 1;
  return (pos);
}

std::pair<int, int>	Arcade::SolarFox::incDown(std::pair<int, int> pos)
{
  if (pos.second < MAP_HEIGHT - 2)
    pos.second += 1;
  return (pos);
}

std::pair<int, int>	Arcade::SolarFox::incLeft(std::pair<int, int> pos)
{
  if (pos.first > 1)
    pos.first -= 1;
  return (pos);
}

std::pair<int, int>	Arcade::SolarFox::incRight(std::pair<int, int> pos)
{
  if (pos.first < MAP_WIDTH - 2)
    pos.first += 1;
  return (pos);
}

Arcade::IGame::GameState	Arcade::SolarFox::gameState() const
{
  if (_end == true)
    return (Arcade::IGame::GameState::ENDED);
  return (Arcade::IGame::GameState::PLAYING);
}

unsigned int	Arcade::SolarFox::getMapWidth() const
{
  return (MAP_WIDTH);
}

unsigned int	Arcade::SolarFox::getMapHeight() const
{
  return (MAP_HEIGHT);
}

void	Arcade::SolarFox::whereAmI()
{
  struct arcade::WhereAmI	*amI;
  char				*buf;

  buf = new char[sizeof(struct arcade::WhereAmI) +
		 (sizeof(struct arcade::Position))];
  amI = new (buf) arcade::WhereAmI;
  amI->type = arcade::CommandType::WHERE_AM_I;
  amI->lenght = 1;
  amI->position[0].x = _ship.first;
  amI->position[0].y = _ship.second;
  std::cout.write(reinterpret_cast<char *>(amI), sizeof(struct arcade::WhereAmI) +
  		  (sizeof(struct arcade::Position)));
  delete[] buf;
}

void	Arcade::SolarFox::getMap()
{
  struct arcade::GetMap *map;
  char			*buf;
  std::pair<unsigned int, unsigned int>	pos;

  buf = new char[sizeof(struct arcade::GetMap) +
		 (sizeof(arcade::TileType) * MAP_HEIGHT * MAP_WIDTH)];
  map = new (buf) arcade::GetMap;
  if (map)
    {
      map->width = MAP_WIDTH;
      map->height = MAP_HEIGHT;
      map->type = arcade::CommandType::GET_MAP;
      pos.second = 0;
      while (pos.second < MAP_HEIGHT)
      	{
      	  pos.first = 0;
      	  while (pos.first < MAP_WIDTH)
      	    {
      	      if (_map[pos.second][pos.first] == 0)
                map->tile[pos.first + (pos.second * MAP_WIDTH)] = arcade::TileType::EMPTY;
      	      else
      		map->tile[pos.first + (pos.second * MAP_WIDTH)] = arcade::TileType::BLOCK;
      	      pos.first += 1;
      	    }
      	  pos.second += 1;
      	}
      pos.first = 0;
      while (pos.first < 4)
      	{
      	  map->tile[_Enemy[pos.first].getPos().first
      		    + (_Enemy[pos.first].getPos().second * MAP_WIDTH)]
      	    = arcade::TileType::EVIL_DUDE;
      	  if (_Enemy[pos.first].getBullet().getPos().first >= 0 &&
      	      _Enemy[pos.first].getBullet().getPos().second >= 0 &&
      	      _Enemy[pos.first].getBullet().getPos().second < MAP_HEIGHT &&
      	      _Enemy[pos.first].getBullet().getPos().first < MAP_WIDTH)
      	    {
      	      map->tile[_Enemy[pos.first].getBullet().getPos().first
      			+ (_Enemy[pos.first].getBullet().getPos().second * MAP_WIDTH)]
      							      = arcade::TileType::EVIL_SHOOT;
      	    }
      	  pos.first += 1;
      	}
      map->tile[_myShoot.getPos().first +
		_myShoot.getPos().second * MAP_WIDTH] = arcade::TileType::MY_SHOOT;
      std::cout.write(reinterpret_cast<char *>(map), sizeof(struct arcade::GetMap) +
       		      (sizeof(arcade::TileType) * MAP_HEIGHT * MAP_WIDTH));
      delete[] buf;
    }
}

void	Arcade::SolarFox::goUp()
{
  eventListener(Arcade::Event(Arcade::Event::AKEY_UP));
}

void	Arcade::SolarFox::goDown()
{
  eventListener(Arcade::Event(Arcade::Event::AKEY_DOWN));
}

void	Arcade::SolarFox::goLeft()
{
  eventListener(Arcade::Event(Arcade::Event::AKEY_LEFT));
}

void	Arcade::SolarFox::goRight()
{
  eventListener(Arcade::Event(Arcade::Event::AKEY_RIGHT));
}

void	Arcade::SolarFox::goForward() {}

void	Arcade::SolarFox::makeShoot() {}

void	Arcade::SolarFox::illegal() {}

void	Arcade::SolarFox::playRound()
{
  render();
}
