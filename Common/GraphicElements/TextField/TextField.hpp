//
// TextField.hpp for TextField in /home/wurmel_a/rendu/cpp_arcade/Common/GraphicElements
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Mon Apr  3 14:01:58 2017 Arnaud WURMEL
// Last update Mon Apr  3 17:46:36 2017 Arnaud WURMEL
//

#ifndef TEXTFIELD_HPP_
# define TEXTFIELD_HPP_

# include <iostream>
# include "Selectable.hpp"

namespace Arcade
{
  class	TextField : public Arcade::Selectable
  {
  public:
    TextField(unsigned int, Arcade::ElementPosition const&);
    ~TextField();

  public:
    virtual void	renderObject(Arcade::IGraphic *, bool isHighlighted = false) const;
    virtual std::string const&	getTitle() const;

  public:
    void		addChar(char);
    void		removeLastChar();

  private:
    std::string		_text;
    unsigned int	_y;
    Arcade::ElementPosition	_pos;
  };
}

#endif /* !TEXTFIELD_HPP_ */
