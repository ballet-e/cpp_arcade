//
// Button.cpp for arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sun Mar 12 14:50:35 2017 Arnaud WURMEL
// Last update Mon Apr  3 22:57:25 2017 Arnaud WURMEL
//

#include <iostream>
#include "Button.hh"

Arcade::Button::Button(std::string const& title,
		       unsigned int y,
		       Arcade::ElementPosition const& pos,
		       std::function<void (void)> func_ptr,
		       Arcade::Button::ButtonType const& type) : Selectable()
{
  _title = title;
  _y = y;
  _pos = pos;
  _func_ptr = func_ptr;
  _type = type;
}

Arcade::Button::ButtonType const&	Arcade::Button::getType() const
{
  return (_type);
}

std::string const&	Arcade::Button::getTitle() const
{
  return (_title);
}

void	Arcade::Button::renderObject(Arcade::IGraphic *graphic, bool isHighlighted) const
{
  std::string		to_print;
  Arcade::Colors	backgroundColor;
  Arcade::Colors	frontColor;

  backgroundColor = Arcade::Colors::ABLACK;
  frontColor = Arcade::Colors::AWHITE;
  to_print = (this->isSelected() ? "* " : "") + _title;
  if (isHighlighted || this->isSelected())
    {
      backgroundColor = Arcade::Colors::AWHITE;
      frontColor = Arcade::Colors::ABLACK;
    }
  if (isEnabled() == false)
    frontColor = Arcade::Colors::AGREY;
  graphic->setText(to_print, _y, _pos, 15, frontColor, backgroundColor);
}

void	Arcade::Button::makeAction() const
{
  _func_ptr();
}

Arcade::Button::~Button() {}
