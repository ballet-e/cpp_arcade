//
// Storage.cpp for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libsokoban/Sokoban
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Thu Apr  6 01:00:04 2017 Victorien Fischer
// Last update Fri Apr  7 02:33:25 2017 Victorien Fischer
//

#include "Storage.hh"

Arcade::Storage::Storage() : _box(false)
{}

Arcade::Storage::~Storage()
{}

Arcade::Floor::Type	Arcade::Storage::getType() const
{
  return (Arcade::Floor::STORAGE);
}

Arcade::Colors		Arcade::Storage::getColor() const
{
  return (Arcade::Colors::ACYAN);
}
