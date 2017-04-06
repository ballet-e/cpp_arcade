//
// Enemy.cpp for  in /home/ballet_e/CPP/cpp_arcade/games/libsolarfox/SolarFox
// 
// Made by Erwan BALLET
// Login   <ballet_e@epitech.net>
// 
// Started on  Wed Apr  5 11:07:23 2017 Erwan BALLET
// Last update Thu Apr  6 16:55:17 2017 Erwan BALLET
//

# include <vector>
# include <utility>
# include "IGame.hh"
# include "Event.hh"
# include "Bullet.hh"
# include "Enemy.hh"

Arcade::Enemy::Enemy()
{
  _pos.first = -1;
  _pos.second = -1;
}

Arcade::Enemy::~Enemy() {}

std::pair<int, int> const&	Arcade::Enemy::getPos() const
{
  return (this->_pos);
}

void				Arcade::Enemy::setPos(int x, int y)
{
  this->_pos.first = x;
  this->_pos.second = y;
}

Arcade::Bullet const&		Arcade::Enemy::getBullet() const
{
  return (this->_bullet);
}

void				Arcade::Enemy::setBullet(Arcade::Bullet const& bullet)
{
  this->_bullet = bullet;
}

void				Arcade::Enemy::setBulletPos(int x, int y)
{
  this->_bullet.setPos(x, y);
}
