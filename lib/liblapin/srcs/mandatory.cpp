//
// main.cpp for Arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
//
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
//
// Started on  Fri Mar 10 21:03:40 2017 Arnaud WURMEL
// Last update Mon Apr  3 22:42:05 2017 Arnaud WURMEL
//

#include "LapinWrapper.hh"
#include "IGraphic.hh"

extern "C" unsigned int	getMagic()
{
  return (MAGIC_NUMBER);
}

extern "C" Arcade::ILibrary	*getLibrary()
{
  return (new Arcade::LapinWrapper());
}
