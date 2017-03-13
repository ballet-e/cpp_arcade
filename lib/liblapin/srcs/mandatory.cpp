//
// main.cpp for Arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
//
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
//
// Started on  Fri Mar 10 21:03:40 2017 Arnaud WURMEL
// Last update Mon Mar 13 18:07:52 2017 Ballet Erwan
//

#include "LIBLAPINWrapper.hh"
#include "IGraphic.hh"
#include "libsfml.hh"

extern "C" unsigned int	getMagic()
{
  return (MAGIC_NUMBER);
}

// extern "C" Arcade::IGraphic	*getLibrary()
// {
//   return (new Arcade::LIBLAPINWrapper());
// }
