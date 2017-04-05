//
// main.cpp for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libsokoban/srcs
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Wed Apr  5 13:11:26 2017 Victorien Fischer
// Last update Wed Apr  5 18:59:51 2017 Victorien Fischer
//

#include "IGame.hh"
#include "Sokoban.hh"
#include "Protocol.hpp"

extern "C" unsigned int getMagic()
{
  return (MAGIC_NUMBER);
}

extern "C" Arcade::Sokoban	*getLibrary()
{
  return (new Arcade::Sokoban());
}

extern "C" void	Play(void)
{
}
