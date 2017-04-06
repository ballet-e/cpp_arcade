//
// Wall.cpp for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libsokoban/Sokoban
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Thu Apr  6 01:00:04 2017 Victorien Fischer
// Last update Thu Apr  6 15:02:52 2017 Victorien Fischer
//

#include "Wall.hh"

Arcade::Wall::Wall()
{}

Arcade::Wall::~Wall()
{}

Arcade::Obstacle::Type	Arcade::Wall::getType() const
{
  return (Arcade::Obstacle::WALL);
}

Arcade::Colors		Arcade::Wall::getColor() const
{
  return (Arcade::Colors::AWHITE);
}
