//
// Text.cpp for cpp_arcade in /home/wurmel_a/rendu/cpp_arcade/lib/libncurses
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Tue Apr  4 23:10:43 2017 Arnaud WURMEL
// Last update Wed Apr  5 11:38:50 2017 Arnaud WURMEL
//

#include "Text.hh"

Arcade::Text::Text(std::string const& print, int x, int y, Arcade::Colors const& font,
		   Arcade::Colors const& back)
{
  _print = print;
  _x = x;
  _y = y;
  _font = font;
  _back = back;
}

Arcade::Colors const&	Arcade::Text::getFont() const
{
  return _font;
}

Arcade::Colors const&	Arcade::Text::getBack() const
{
  return _back;
}

std::string const&	Arcade::Text::getText() const
{
  return _print;
}

int	Arcade::Text::getX() const
{
  return _x;
}

int	Arcade::Text::getY() const
{
  return _y;
}

Arcade::Text::~Text() {}
