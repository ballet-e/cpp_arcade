//
// main.cpp for Arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Fri Mar 10 21:03:40 2017 Arnaud WURMEL
// Last update Sat Mar 11 22:40:31 2017 Arnaud WURMEL
//

#include "SFMLWrapper.hh"
#include "libsfml.hh"
#include "IGraphic.hh"

extern "C" unsigned int	getMagic()
{
  return (MAGIC_NUMBER);
}

extern "C" Arcade::IGraphic	*getLibrary()
{
  return (new Arcade::SFMLWrapper());
}
