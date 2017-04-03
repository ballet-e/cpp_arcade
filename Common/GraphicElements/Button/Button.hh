//
// Button.hh for arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sun Mar 12 14:43:37 2017 Arnaud WURMEL
// Last update Mon Apr  3 17:29:44 2017 Arnaud WURMEL
//

#ifndef BUTTON_HH_
# define BUTTON_HH_

# include <functional>
# include <algorithm>
# include <utility>
# include <string>
# include "Selectable.hpp"

namespace Arcade
{
  class	Button : public Arcade::Selectable
  {
  public:
    Button(std::string const&, unsigned int,
	   Arcade::ElementPosition const&,
	   std::function<void (void)>,
	   Arcade::Button::ButtonType const& type = ButtonType::VALIDATE);
    ~Button();


  public:
    virtual void	renderObject(Arcade::IGraphic *, bool isHighlighted = false) const;

  public:
    void		makeAction() const;

  public:
    Arcade::Button::ButtonType const&	getType() const;
    std::string const&			getTitle() const;

  private:
    std::string					_title;
    unsigned int				_y;
    Arcade::ElementPosition			_pos;
    Arcade::Button::ButtonType			_type;
    std::function<void (void)>			_func_ptr;
  };
}

#endif /* !BUTTON_HH_ */
