//
// main.cpp for Arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Fri Mar 10 21:03:40 2017 Arnaud WURMEL
// Last update Sun Apr  9 19:40:49 2017 Arnaud WURMEL
//

#include <map>
#include <string>
#include <functional>
#include <utility>
#include <iostream>
#include <fstream>
#include "Protocol.hpp"
#include "IGame.hh"
#include "Snake.hh"

extern "C" unsigned int	getMagic()
{
  return (MAGIC_NUMBER);
}

extern "C" Arcade::ILibrary	*getLibrary()
{
  return (new Arcade::Snake());
}

extern "C" void	Play(void)
{
  Arcade::Snake	snake;
  arcade::CommandType		cmd;
  std::map<arcade::CommandType, std::function<void ()>>	function_ptr;

  function_ptr.insert(std::make_pair(arcade::CommandType::WHERE_AM_I, std::bind(&Arcade::Snake::whereAmI, &snake)));
  function_ptr.insert(std::make_pair(arcade::CommandType::GET_MAP, std::bind(&Arcade::Snake::getMap, &snake)));
  function_ptr.insert(std::make_pair(arcade::CommandType::GO_UP, std::bind(&Arcade::Snake::goUp, &snake)));
  function_ptr.insert(std::make_pair(arcade::CommandType::GO_DOWN, std::bind(&Arcade::Snake::goDown, &snake)));
  function_ptr.insert(std::make_pair(arcade::CommandType::GO_LEFT, std::bind(&Arcade::Snake::goLeft, &snake)));
  function_ptr.insert(std::make_pair(arcade::CommandType::GO_RIGHT, std::bind(&Arcade::Snake::goRight, &snake)));
  function_ptr.insert(std::make_pair(arcade::CommandType::GO_FORWARD, std::bind(&Arcade::Snake::goForward, &snake)));
  function_ptr.insert(std::make_pair(arcade::CommandType::SHOOT, std::bind(&Arcade::Snake::makeShoot, &snake)));
  function_ptr.insert(std::make_pair(arcade::CommandType::ILLEGAL, std::bind(&Arcade::Snake::illegal, &snake)));
  function_ptr.insert(std::make_pair(arcade::CommandType::PLAY, std::bind(&Arcade::Snake::playRound, &snake)));
  while (true)
    {
      std::cin.read(reinterpret_cast<char *>(&cmd), sizeof(arcade::CommandType));
      if (function_ptr.find(cmd) != function_ptr.end())
	function_ptr[cmd]();
      if (std::cin.eof())
	break;
    }
}
