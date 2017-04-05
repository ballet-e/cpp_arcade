//
// Bullet.cpp for  in /home/ballet_e/CPP/cpp_arcade/games/libsolarfox/SolarFox
// 
// Made by Erwan BALLET
// Login   <ballet_e@epitech.net>
// 
// Started on  Wed Apr  5 09:02:38 2017 Erwan BALLET
// Last update Wed Apr  5 16:49:33 2017 Erwan BALLET
//

# include <vector>
# include <utility>
# include "IGame.hh"
# include "Event.hh"
# include "Bullet.hh"

Arcade::Bullet::Bullet()
{
  this->_pos.first = -1;
  this->_pos.second = -1;
}

Arcade::Bullet::~Bullet() {}

std::pair<int, int> const&	Arcade::Bullet::getPos() const
{
  return (this->_pos);
}

void				Arcade::Bullet::setPos(int x, int y)
{
  this->_pos.first = x;
  this->_pos.second = y;
}

Arcade::Bullet::Directions const&	Arcade::Bullet::getDir() const
{
  return (this->_dir);
}

void				Arcade::Bullet::setDir(Arcade::Bullet::Directions const& dir)
{
  this->_dir = dir;
}
