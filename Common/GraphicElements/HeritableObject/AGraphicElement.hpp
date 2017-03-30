//
// AGraphicElement.hpp for arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml/GraphicElements/HeritableObject
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Wed Mar 15 22:45:59 2017 Arnaud WURMEL
// Last update Thu Mar 16 02:36:20 2017 Arnaud WURMEL
//

#ifndef AGRAPHICELEMENT_HPP_
# define AGRAPHICELEMENT_HPP_

# include "IGraphic.hh"

namespace	Arcade
{
  class	AGraphicElement
  {
  public:
    virtual void	renderObject(Arcade::IGraphic *, bool isHighlighted = false) const = 0;
    virtual ~AGraphicElement() {}
  };
}

#endif /* !AGRAPHICELEMENT_HPP_ */
