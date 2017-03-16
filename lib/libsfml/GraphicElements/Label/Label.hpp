//
// Label.hpp for arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml/GraphicElements
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Thu Mar 16 00:59:16 2017 Arnaud WURMEL
// Last update Thu Mar 16 01:06:42 2017 Arnaud WURMEL
//

#ifndef LABEL_HPP_
# define LABEL_HPP_

# include <string>
# include "AGraphicElement.hpp"

namespace	Arcade
{
  class	Label
  {
  public:
    Label(std::string const&, unsigned int, Arcade::ElementPosition const&,
	  unsigned int, Arcade::Colors const&);
    ~Label();

  public:
    virtual void	renderObject(Arcade::IGraphic *, bool isHighlighted = false) const;

  private:
    std::string			_title;
    unsigned int		_y;
    Arcade::ElementPosition	_pos;
    unsigned int		_fontSize;
    Arcade::Colors		_fontColor;
  };
}

#endif /* !LABEL_HPP_ */
