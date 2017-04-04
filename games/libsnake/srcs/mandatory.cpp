//
// main.cpp for Arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Fri Mar 10 21:03:40 2017 Arnaud WURMEL
// Last update Tue Apr  4 13:07:55 2017 Arnaud WURMEL
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

  // function_ptr.push_back(std::bind(&Arcade::Snake::whereAmI, &snake, std::placeholders::_1));
  // function_ptr.insert(std::make_pair(arcade::CommandType::WHERE_AM_I, std::bind(&Arcade::Snake::whereAmI, &snake, std::placeholders::_1)));
  // function_ptr.insert(std::make_pair(arcade::CommandType::GET_MAP, std::bind(&Arcade::Snake::getMap, &snake, std::placeholders::_1)));
  // function_ptr.insert(std::make_pair(arcade::CommandType::GO_UP, std::bind(&Arcade::Snake::goUp, &snake, std::placeholders::_1)));
  // function_ptr.insert(std::make_pair(arcade::CommandType::GO_DOWN, std::bind(&Arcade::Snake::goDown, &snake, std::placeholders::_1)));
  // function_ptr.insert(std::make_pair(arcade::CommandType::GO_LEFT, std::bind(&Arcade::Snake::goLeft, &snake, std::placeholders::_1)));
  // function_ptr.insert(std::make_pair(arcade::CommandType::GO_RIGHT, std::bind(&Arcade::Snake::goRight, &snake, std::placeholders::_1)));
  // function_ptr.insert(std::make_pair(arcade::CommandType::GO_FORWARD, std::bind(&Arcade::Snake::goForward, &snake, std::placeholders::_1)));
  // function_ptr.insert(std::make_pair(arcade::CommandType::SHOOT, std::bind(&Arcade::Snake::makeShoot, &snake, std::placeholders::_1)));
  // function_ptr.insert(std::make_pair(arcade::CommandType::ILLEGAL, std::bind(&Arcade::Snake::illegal, &snake, std::placeholders::_1)));
  // function_ptr.insert(std::make_pair(arcade::CommandType::PLAY, std::bind(&Arcade::Snake::playRound, &snake, std::placeholders::_1)));
  while (true)
    {
      std::cin.read(reinterpret_cast<char *>(&cmd), sizeof(arcade::CommandType));
      //      std::cerr << "Cmd: " <<  cmd << std::endl;
      if (cmd == arcade::CommandType::WHERE_AM_I)
	snake.whereAmI();
      else if (cmd == arcade::CommandType::GET_MAP)
	snake.getMap();
      else if (cmd == arcade::CommandType::GO_UP)
	snake.goUp();
      else if (cmd == arcade::CommandType::GO_DOWN)
	snake.goDown();
      else if (cmd == arcade::CommandType::GO_LEFT)
	snake.goLeft();
      else if (cmd == arcade::CommandType::GO_RIGHT)
	snake.goRight();
      else if (cmd == arcade::CommandType::GO_FORWARD)
	snake.goForward();
      else if (cmd == arcade::CommandType::SHOOT)
	snake.makeShoot();
      else if (cmd == arcade::CommandType::ILLEGAL)
	snake.illegal();
      else
	snake.playRound();
      if (std::cin.eof())
	break;
    }
}
