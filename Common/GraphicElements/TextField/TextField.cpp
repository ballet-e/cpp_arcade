//
// TextField.cpp for cpp_arcade in /home/wurmel_a/rendu/cpp_arcade/Common/GraphicElements
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Mon Apr  3 14:01:45 2017 Arnaud WURMEL
// Last update Tue Apr  4 15:05:13 2017 Arnaud WURMEL
//

#include "TextField.hpp"

Arcade::TextField::TextField(unsigned int y,
			     Arcade::ElementPosition const& pos) : Selectable()
{
  _text = "";
  _y = y;
  _pos = pos;
  setSelected(true);
}

void		Arcade::TextField::renderObject(Arcade::IGraphic *graphic,
						bool isHighlighted) const
{
  std::string		to_print;
  Arcade::Colors	backgroundColor;
  Arcade::Colors	frontColor;

  backgroundColor = Arcade::Colors::ABLACK;
  frontColor = Arcade::Colors::AWHITE;
  to_print = getTitle();
  to_print += "_";
  if (isHighlighted)
    {
      backgroundColor = Arcade::Colors::AWHITE;
      frontColor = Arcade::Colors::ABLACK;
    }
  graphic->setText(to_print, _y, _pos, 15, frontColor, backgroundColor);
}

std::string const&	Arcade::TextField::getTitle() const
{
  return (_text);
}

void	Arcade::TextField::addChar(char to_append)
{
  char	buf[2];

  if (to_append == -1)
    {
      removeLastChar();
      return ;
    }
  buf[0] = to_append;
  buf[1] = '\0';
  _text.append(buf);
}

void	Arcade::TextField::removeLastChar()
{
  if (_text.size() > 0)
    _text.pop_back();
}

Arcade::TextField::~TextField()
{

}
