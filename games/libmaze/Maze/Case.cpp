//
// Case.cpp for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libmaze/Maze
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Thu Apr  6 14:52:35 2017 Victorien Fischer
// Last update Sun Apr  9 16:37:16 2017 Victorien Fischer
//

#include "Case.hh"

Arcade::Case::Case(int x, int y, Arcade::Obstacle *obs, Arcade::Floor *flr)
  : _x(x), _y(y), _obs(obs), _flr(flr)
{}

Arcade::Case::Case(Arcade::Case const	&other) : _x(other.getX()), _y(other.getY()), _obs(other.getObstacle()), _flr(other.getFloor())
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
  if (_flr)
    return (_flr->getColor());
  return (Arcade::Colors::AGREY);
}

Arcade::Obstacle	*Arcade::Case::getObstacle() const
{
  return (_obs);
}

Arcade::Floor		*Arcade::Case::getFloor() const
{
  return (_flr);
}

void			Arcade::Case::setObstacle(Arcade::Obstacle *obs)
{
  _obs = obs;
}

void			Arcade::Case::setFloor(Arcade::Floor *flr)
{
  _flr = flr;
}
