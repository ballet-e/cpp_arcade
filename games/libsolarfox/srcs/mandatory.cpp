//
// mandatory.cpp for  in /home/ballet/CPP/cpp_arcade/games/libsolarfox
//
// Made by BALLET Erwan
// Login   <ballet@epitech.net>
//
// Started on  Tue Apr  4 10:46:34 2017 BALLET Erwan
// Last update Tue Apr  4 11:00:33 2017 Ballet Erwan
//

#include <map>
#include <string>
#include <functional>
#include <utility>
#include <iostream>
#include <fstream>
#include "Protocol.hpp"
#include "IGame.hh"
#include "SolarFox.hh"

extern "C" unsigned int	getMagic()
{
  return (MAGIC_NUMBER);
}

extern "C" Arcade::ILibrary	*getLibrary()
{
  return (new Arcade::SolarFox());
}

extern "C" void	Play(void)
{
  Arcade::SolarFox	solar_fox;
  arcade::CommandType		cmd;

  // function_ptr.push_back(std::bind(&Arcade::SolarFox::whereAmI, &solar_fox, std::placeholders::_1));
  // function_ptr.insert(std::make_pair(arcade::CommandType::WHERE_AM_I, std::bind(&Arcade::SolarFox::whereAmI, &solar_fox, std::placeholders::_1)));
  // function_ptr.insert(std::make_pair(arcade::CommandType::GET_MAP, std::bind(&Arcade::SolarFox::getMap, &solar_fox, std::placeholders::_1)));
  // function_ptr.insert(std::make_pair(arcade::CommandType::GO_UP, std::bind(&Arcade::SolarFox::goUp, &solar_fox, std::placeholders::_1)));
  // function_ptr.insert(std::make_pair(arcade::CommandType::GO_DOWN, std::bind(&Arcade::SolarFox::goDown, &solar_fox, std::placeholders::_1)));
  // function_ptr.insert(std::make_pair(arcade::CommandType::GO_LEFT, std::bind(&Arcade::SolarFox::goLeft, &solar_fox, std::placeholders::_1)));
  // function_ptr.insert(std::make_pair(arcade::CommandType::GO_RIGHT, std::bind(&Arcade::SolarFox::goRight, &solar_fox, std::placeholders::_1)));
  // function_ptr.insert(std::make_pair(arcade::CommandType::GO_FORWARD, std::bind(&Arcade::SolarFox::goForward, &solar_fox, std::placeholders::_1)));
  // function_ptr.insert(std::make_pair(arcade::CommandType::SHOOT, std::bind(&Arcade::SolarFox::makeShoot, &solar_fox, std::placeholders::_1)));
  // function_ptr.insert(std::make_pair(arcade::CommandType::ILLEGAL, std::bind(&Arcade::SolarFox::illegal, &solar_fox, std::placeholders::_1)));
  // function_ptr.insert(std::make_pair(arcade::CommandType::PLAY, std::bind(&Arcade::SolarFox::playRound, &solar_fox, std::placeholders::_1)));
  while (true)
    {
      std::cin.read(reinterpret_cast<char *>(&cmd), sizeof(arcade::CommandType));
      //      std::cerr << "Cmd: " <<  cmd << std::endl;
      if (cmd == arcade::CommandType::WHERE_AM_I)
	solar_fox.whereAmI();
      else if (cmd == arcade::CommandType::GET_MAP)
	solar_fox.getMap();
      else if (cmd == arcade::CommandType::GO_UP)
	solar_fox.goUp();
      else if (cmd == arcade::CommandType::GO_DOWN)
	solar_fox.goDown();
      else if (cmd == arcade::CommandType::GO_LEFT)
	solar_fox.goLeft();
      else if (cmd == arcade::CommandType::GO_RIGHT)
	solar_fox.goRight();
      else if (cmd == arcade::CommandType::GO_FORWARD)
	solar_fox.goForward();
      else if (cmd == arcade::CommandType::SHOOT)
	solar_fox.makeShoot();
      else if (cmd == arcade::CommandType::ILLEGAL)
	solar_fox.illegal();
      else
	solar_fox.playRound();
      if (std::cin.eof())
	break;
    }
}

 int	main(void)
{
  Play();
  return 0;
}
