//
// main.cpp for Arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Fri Mar 10 21:03:40 2017 Arnaud WURMEL
// Last update Wed Mar 22 11:46:25 2017 Arnaud WURMEL
//

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
  int		cmd;

  while (true)
    {
      std::cin.read(reinterpret_cast<char *>(&cmd), sizeof(int));
      std::cout << cmd << std::endl;
      if (std::cin.eof())
	break;
    }
}

int	main(void)
{
  Play();
  return 0;
}
