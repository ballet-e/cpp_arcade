//
// SFMLWrapper.cpp for arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sat Mar 11 22:36:02 2017 Arnaud WURMEL
// Last update Sat Mar 11 23:38:09 2017 Arnaud WURMEL
//

#include "SFMLWrapper.hh"

Arcade::SFMLWrapper::SFMLWrapper()
{
  _window = NULL;
}

bool	Arcade::SFMLWrapper::renderWindowStart()
{
  sf::Event	event;

  while (_window->isOpen())
    {
      while (_window->pollEvent(event))
	{
	  if (event.type == sf::Event::Closed ||
	      (event.type == sf::Event::KeyPressed &&
	       event.key.code == sf::Keyboard::Escape))
	    _window->close();
	}
      _window->display();
    }
  return true;
}

bool	Arcade::SFMLWrapper::createWindow(unsigned int width, unsigned int height)
{
  _window = new sf::Window(sf::VideoMode(width, height), "SFMLWrapper", sf::Style::Close);
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

