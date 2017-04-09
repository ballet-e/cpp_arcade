//
// main.cpp for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libmaze/srcs
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Wed Apr  5 13:11:26 2017 Victorien Fischer
// Last update Sun Apr  9 16:23:07 2017 Victorien Fischer
//

#include "IGame.hh"
#include "Maze.hh"
#include "Protocol.hpp"

extern "C" unsigned int getMagic()
{
  return (MAGIC_NUMBER);
}

extern "C" Arcade::Maze	*getLibrary()
{
  return (new Arcade::Maze());
}

extern "C" void	Play(void)
{
}
