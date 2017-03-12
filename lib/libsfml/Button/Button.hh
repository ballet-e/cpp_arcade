//
// Button.hh for arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sun Mar 12 14:43:37 2017 Arnaud WURMEL
// Last update Sun Mar 12 23:46:03 2017 Arnaud WURMEL
//

#ifndef BUTTON_HH_
# define BUTTON_HH_

# include <string>
# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>

namespace Arcade
{
  class	Button
  {
  public:
    enum ButtonType
      {
	VALIDATE,
	RETURN,
	SELECT
      };
    enum ButtonPos
      {
	CENTER,
	LEFT,
	RIGHT
      };
  public:
    Button(std::string const&, unsigned int, Arcade::Button::ButtonPos, Arcade::Button::ButtonType, bool enable = true);
    ~Button();

  public:
    void	setSelected(bool);
    bool	isSelected() const;
    Arcade::Button::ButtonType	getType() const;
    void	enable(bool);
    bool	isEnabled() const;

    std::string const&	getTitle() const;

  public:
    void	draw(sf::RenderWindow&, bool onOverlay = false);

  private:
    bool		_selected;
    ButtonPos		_pos;
    unsigned int	_y;
    std::string		_title;
    Arcade::Button::ButtonType	_type;
    bool	_enable;
  };
}

#endif /* !BUTTON_HH_ */
