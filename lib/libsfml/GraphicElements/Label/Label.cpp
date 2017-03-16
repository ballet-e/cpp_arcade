//
// Label.cpp for arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml/GraphicElements
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Thu Mar 16 01:00:21 2017 Arnaud WURMEL
// Last update Thu Mar 16 01:05:53 2017 Arnaud WURMEL
//

#include "Label.hpp"

Arcade::Label::Label(std::string const& title, unsigned int y,
		     Arcade::ElementPosition const& pos,
		     unsigned int fontSize,
		     Arcade::Colors const& fontColor)
{
  _pos = pos;
  _title = title;
  _y = y;
  _fontSize = fontSize;
  _fontColor = fontColor;
}

void	Arcade::Label::renderObject(Arcade::IGraphic *graphic, bool isHighlighted) const
{
  static_cast<void>(isHighlighted);
  graphic->setText(_title, _y, _pos, _fontSize, _fontColor, Arcade::Colors::BLACK);
}

Arcade::Label::~Label() {}
