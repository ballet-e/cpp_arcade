//
// Selectable.hpp for cpp_arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml/GraphicElements
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Wed Mar 15 22:36:52 2017 Arnaud WURMEL
// Last update Mon Apr  3 17:45:51 2017 Arnaud WURMEL
//

#ifndef SELECTABLE_HPP_
# define SELECTABLE_HPP_

# include <iostream>
# include "IGraphic.hh"
# include "AGraphicElement.hpp"

namespace	Arcade
{
  class		Selectable : public Arcade::AGraphicElement
  {
  public:
    enum	ButtonType
      {
	VALIDATE,
	SELECT,
	RETURN,
	UNKNOWN
      };
  public:
    Selectable();
    ~Selectable();

  public:
    virtual void	renderObject(Arcade::IGraphic *, bool isHighlighted = false) const = 0;
    virtual Arcade::Selectable::ButtonType const&	getType() const;
    virtual std::string const&	getTitle() const = 0;

  public:
    bool	isSelected() const;
    void	setSelected(bool);
    bool	isEnabled() const;
    void	enable(bool);

  protected:
    bool	_selected;
    bool	_enable;
    Arcade::Selectable::ButtonType	_type;
  };
}

#endif /* !SELECTABLE_HPP_ */
