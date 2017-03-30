//
// Selectable.cpp for arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml/GraphicElements
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Wed Mar 15 22:35:33 2017 Arnaud WURMEL
// Last update Wed Mar 15 22:55:15 2017 Arnaud WURMEL
//

#include "Selectable.hpp"

Arcade::Selectable::Selectable()
{
  _selected = false;
  _enable = true;
}

void	Arcade::Selectable::setSelected(bool value)
{
  _selected = value;
}

bool	Arcade::Selectable::isSelected() const
{
  return _selected;
}

void	Arcade::Selectable::enable(bool value)
{
  _enable = value;
}

bool	Arcade::Selectable::isEnabled() const
{
  return (_enable);
}

Arcade::Selectable::~Selectable() {}
