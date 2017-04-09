//
// Destination.cpp for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libmaze/Maze
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Thu Apr  6 01:00:04 2017 Victorien Fischer
// Last update Sun Apr  9 16:27:00 2017 Victorien Fischer
//

#include "Destination.hh"

Arcade::Destination::Destination() : _box(false)
{}

Arcade::Destination::~Destination()
{}

Arcade::Floor::Type	Arcade::Destination::getType() const
{
  return (Arcade::Floor::DESTINATION);
}

Arcade::Colors		Arcade::Destination::getColor() const
{
  return (Arcade::Colors::ACYAN);
}
