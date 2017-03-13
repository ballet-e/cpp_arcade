//
// Snake.cpp for Arcade in /home/wurmel/rendu/cpp_arcade/games/libsnake
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Mon Mar 13 16:19:28 2017 Arnaud WURMEL
// Last update Mon Mar 13 16:27:16 2017 Arnaud WURMEL
//

#include "Snake.hh"

Arcade::Snake::Snake()
{

}

void	Arcade::Snake::setUpGraphics(IGraphic *ref)
{
  _graphic_library = ref;
}

Arcade::LibraryType	Arcade::Snake::getLibraryType() const
{
  return (Arcade::GAME);
}

Arcade::Snake::~Snake() {}
