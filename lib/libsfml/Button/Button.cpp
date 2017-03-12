//
// Button.cpp for arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sun Mar 12 14:50:35 2017 Arnaud WURMEL
// Last update Sun Mar 12 23:46:38 2017 Arnaud WURMEL
//

#include <iostream>
#include "Button.hh"

Arcade::Button::Button(std::string const& title, unsigned int y, Arcade::Button::ButtonPos pos,
		       Arcade::Button::ButtonType type, bool enable)
{
  _title = title;
  _pos = pos;
  _y = y;
  _selected = false;
  _type = type;
  _enable = enable;
}

Arcade::Button::~Button() {}

void	Arcade::Button::setSelected(bool value)
{
  _selected = value;
}

bool	Arcade::Button::isSelected() const
{
  return (_selected);
}

Arcade::Button::ButtonType	Arcade::Button::getType() const
{
  return _type;
}

void	Arcade::Button::enable(bool value)
{
  _enable = value;
}

bool	Arcade::Button::isEnabled() const
{
  return (_enable);
}

void	Arcade::Button::draw(sf::RenderWindow& window, bool onOverlay)
{
  sf::Text	text;
  sf::Font	font;
  int		x;

  if (!font.loadFromFile("Ressources/font.ttf"))
    std::cerr << "Can't load font.ttf" << std::endl;
  else
    text.setFont(font);
  text.setString((_selected ? "* " : "") + _title);
  text.setCharacterSize(15);
  x = 0;
  if (_pos == Arcade::Button::CENTER)
    x = (window.getView().getSize().x / 2 - (text.getLocalBounds().width / 2));
  else if (_pos == Arcade::Button::RIGHT)
    x = (window.getView().getSize().x / 2) + 50;
  else
    x = ((window.getView().getSize().x / 2) - 50) - (text.getLocalBounds().width);
  text.setPosition(x, _y);
  if (_selected || onOverlay)
    {
      sf::FloatRect backgroundRect = text.getLocalBounds();
      sf::RectangleShape background(sf::Vector2f(backgroundRect.width + 4, backgroundRect.height + 4));
      
      background.setFillColor(sf::Color::White);
      text.setColor(sf::Color::Black);
      background.setPosition(x - 2, _y);
      window.draw(background);
    }
  else
    text.setColor(_enable ? sf::Color::White : sf::Color(120, 120, 120));
  window.draw(text);
}

std::string const&	Arcade::Button::getTitle() const
{
  return (_title);
}
