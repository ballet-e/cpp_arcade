//
// SFMLWrapper.cpp for arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sat Mar 11 22:36:02 2017 Arnaud WURMEL
// Last update Sun Mar 12 14:37:23 2017 Arnaud WURMEL
//

#include <iostream>
#include "SFMLWrapper.hh"

Arcade::SFMLWrapper::SFMLWrapper()
{
  _window = NULL;
}

void	Arcade::SFMLWrapper::drawTitle()
{
  sf::Text	text;
  sf::Font	font;

  if (!font.loadFromFile("Ressources/font.ttf"))
    std::cerr << "Can't load font.ttf" << std::endl;
  else
    text.setFont(font);
  text.setString("Arcade");
  text.setCharacterSize(50);
  text.setColor(sf::Color::Blue);
  text.setPosition(600 - (text.getLocalBounds().width / 2), 10);
  _window->draw(text);
}

bool	Arcade::SFMLWrapper::renderWindowStart()
{
  sf::Event	e;

  if (_window)
    {
      _window->close();
      delete _window;
    }
  Arcade::SFMLWrapper::createWindow(1200, 900);
  while (_window->isOpen())
    {
      while (_window->pollEvent(e))
	{
	  if (e.type == sf::Event::Closed)
	    _window->close();
	}
      drawTitle();
      _window->display();
    }
  return true;
}

bool	Arcade::SFMLWrapper::createWindow(unsigned int width, unsigned int height)
{
  _window = new sf::RenderWindow(sf::VideoMode(width, height), "SFMLWrapper", sf::Style::Close);
  return true;
}

bool	Arcade::SFMLWrapper::drawSquare64x64(unsigned int x, unsigned int y,
					     unsigned int color)
{
  static_cast<void>(x);
  static_cast<void>(y);
  static_cast<void>(color);
  return (false);
}

Arcade::LibraryType	Arcade::SFMLWrapper::getLibraryType() const
{
  return (Arcade::Graphic);
}

Arcade::SFMLWrapper::~SFMLWrapper()
{
  if (_window)
    delete _window;
}
