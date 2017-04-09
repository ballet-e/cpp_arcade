//
// main.cpp for Arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Fri Mar 10 21:03:40 2017 Arnaud WURMEL
// Last update Sun Apr  9 19:41:28 2017 Arnaud WURMEL
//

#include <map>
#include <string>
#include <functional>
#include <utility>
#include <iostream>
#include <fstream>
#include "Protocol.hpp"
#include "IGame.hh"
#include "Pacman.hh"

extern "C" unsigned int	getMagic()
{
  return (MAGIC_NUMBER);
}

extern "C" Arcade::ILibrary	*getLibrary()
{
  return (new Arcade::Pacman());
}

extern "C" void	Play(void)
{
  Arcade::Pacman	pacman;
  arcade::CommandType		cmd;
  std::map<arcade::CommandType, std::function<void ()>>	function_ptr;

  function_ptr.insert(std::make_pair(arcade::CommandType::WHERE_AM_I, std::bind(&Arcade::Pacman::whereAmI, &pacman)));
  function_ptr.insert(std::make_pair(arcade::CommandType::GET_MAP, std::bind(&Arcade::Pacman::getMap, &pacman)));
  function_ptr.insert(std::make_pair(arcade::CommandType::GO_UP, std::bind(&Arcade::Pacman::goUp, &pacman)));
  function_ptr.insert(std::make_pair(arcade::CommandType::GO_DOWN, std::bind(&Arcade::Pacman::goDown, &pacman)));
  function_ptr.insert(std::make_pair(arcade::CommandType::GO_LEFT, std::bind(&Arcade::Pacman::goLeft, &pacman)));
  function_ptr.insert(std::make_pair(arcade::CommandType::GO_RIGHT, std::bind(&Arcade::Pacman::goRight, &pacman)));
  function_ptr.insert(std::make_pair(arcade::CommandType::GO_FORWARD, std::bind(&Arcade::Pacman::goForward, &pacman)));
  function_ptr.insert(std::make_pair(arcade::CommandType::SHOOT, std::bind(&Arcade::Pacman::makeShoot, &pacman)));
  function_ptr.insert(std::make_pair(arcade::CommandType::ILLEGAL, std::bind(&Arcade::Pacman::illegal, &pacman)));
  function_ptr.insert(std::make_pair(arcade::CommandType::PLAY, std::bind(&Arcade::Pacman::playRound, &pacman)));
  while (true)
    {
      std::cin.read(reinterpret_cast<char *>(&cmd), sizeof(arcade::CommandType));
      if (function_ptr.find(cmd) != function_ptr.end())
	function_ptr[cmd]();
      if (std::cin.eof())
	break;
    }
}
