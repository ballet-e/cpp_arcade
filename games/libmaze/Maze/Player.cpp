//
// Player.cpp for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libmaze/Maze
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Fri Apr  7 00:22:55 2017 Victorien Fischer
// Last update Sun Apr  9 16:29:07 2017 Victorien Fischer
//

#include "Player.hh"

Arcade::Player::Player()
{}

Arcade::Player::~Player()
{}

Arcade::Obstacle::Type	Arcade::Player::getType() const
{
  return (Arcade::Obstacle::PLAYER);
}

Arcade::Colors		Arcade::Player::getColor() const
{
  return (Arcade::Colors::APINK);
}
