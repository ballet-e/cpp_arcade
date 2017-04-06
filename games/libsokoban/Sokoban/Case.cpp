//
// Case.cpp for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libsokoban/Sokoban
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Thu Apr  6 14:52:35 2017 Victorien Fischer
// Last update Thu Apr  6 15:06:13 2017 Victorien Fischer
//

#include "Case.hh"

Arcade::Case::Case(int x, int y, Arcade::Obstacle *obs) : _x(x), _y(y), _obs(obs)
{}

Arcade::Case::Case(Arcade::Case const	&other) : _x(other.getX()), _y(other.getY()), _obs(other.getObstacle())
{}

Arcade::Case::~Case()
{}

int		Arcade::Case::getX() const
{
  return (_x);
}

int		Arcade::Case::getY() const
{
  return (_y);
}

Arcade::Colors	Arcade::Case::getColor() const
{
  if (_obs)
    return (_obs->getColor());
  return (Arcade::Colors::AGREY);
}

Arcade::Obstacle	*Arcade::Case::getObstacle() const
{
  return (_obs);
}

void			Arcade::Case::setObstacle(Arcade::Obstacle *obs)
{
  _obs = obs;
}
