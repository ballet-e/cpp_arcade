//
// mandatory.cpp for  in /home/ballet/CPP/cpp_arcade/games/libsolarfox
//
// Made by BALLET Erwan
// Login   <ballet@epitech.net>
//
// Started on  Tue Apr  4 10:46:34 2017 BALLET Erwan
// Last update Sun Apr  9 22:06:38 2017 Arnaud WURMEL
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
