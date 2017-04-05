//
// Box.cpp for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libsokoban/Sokoban
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Thu Apr  6 01:00:04 2017 Victorien Fischer
// Last update Thu Apr  6 01:02:21 2017 Victorien Fischer
//

#include "Box.hh"

Arcade::Box::Box()
{}

Arcade::Box::~Box()
{}

Arcade::Obstacle::Type	Arcade::Box::getType() const
{
  return (Arcade::Obstacle::BOX);
}
