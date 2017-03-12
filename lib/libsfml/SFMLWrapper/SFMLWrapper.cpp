//
// SFMLWrapper.cpp for arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sat Mar 11 22:36:02 2017 Arnaud WURMEL
// Last update Sun Mar 12 19:37:59 2017 Arnaud WURMEL
//

#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <exception>
#include "SFMLWrapper.hh"

Arcade::SFMLWrapper::SFMLWrapper()
{
  _window = NULL;
  _button_list.clear();
}

void	Arcade::SFMLWrapper::drawTitle()
{
  sf::Text	text;
  sf::Font	font;
  std::string::const_iterator	it;
  std::string	to_disp = "Arcade";
  sf::Color	tab[5];

  tab[0] = sf::Color(134, 223, 216);
  tab[1] = sf::Color(239, 177, 255);
  tab[2] = sf::Color(131, 91, 127);
  tab[3] = sf::Color(102, 165, 99);
  tab[4] = sf::Color(240, 255, 121);
  if (!font.loadFromFile("Ressources/font.ttf"))
    std::cerr << "Can't load font.ttf" << std::endl;
  else
    text.setFont(font);
  text.setCharacterSize(50);
  text.setColor(sf::Color::Blue);
  it = to_disp.begin();
  while (it != to_disp.end())
    {
      text.setString("Arcade");
      text.setPosition((600 - (text.getLocalBounds().width / 2)) + ((it - to_disp.begin()) * 52), 10);
      text.setString(*it);
      text.setColor(tab[(it - to_disp.begin()) % 5]);
      _window->draw(text);
      ++it;
    }
  text.setString("Choisir une librairie pour lancer le jeu");
  text.setCharacterSize(15);
  text.setColor(sf::Color::White);
  text.setPosition(600 - (text.getLocalBounds().width / 2), 120);
  _window->draw(text);
}

// Rework std::exception to replace by exception classes.
void	Arcade::SFMLWrapper::getAllLibrary()
{
  DIR	*dir;
  struct dirent	*dent;
  unsigned int	y;

  _button_list.clear();
  dir = opendir("./lib");
  if (dir == NULL)
    {
      std::cerr << "Can't load directory" << std::endl;
      throw std::exception();
    }
  y = 200;
  while ((dent = readdir(dir)))
    {
      if (dent->d_type == DT_REG && std::string(dent->d_name).find(".so") != std::string::npos)
	{
	  _button_list.push_back(Button(dent->d_name, y, Arcade::Button::CENTER, Arcade::Button::SELECT));
	  y += 30;
	}
    }
  closedir(dir);
  if (_current_pos - _button_list.begin() > _button_list.size())
    _current_pos = _button_list.begin();
}

void	Arcade::SFMLWrapper::drawWindow()
{
  std::vector<Arcade::Button>::iterator	it;

  _window->clear();
  drawTitle();
  getAllLibrary();
  it = _button_list.begin();
  while (it != _button_list.end())
    {
      if (it == _current_pos)
	(*it).setSelected(true);
      (*it).draw(*_window);
      if (it == _current_pos)
	(*it).setSelected(false);
      ++it;
    }
  _window->display();
}

bool	Arcade::SFMLWrapper::keyboardHandler(sf::Event const& e)
{
  if (e.key.code == sf::Keyboard::Escape)
    {
      _window->close();
      return false;
    }
  if (e.key.code == sf::Keyboard::Down)
    {
      ++_current_pos;
      if (_current_pos == _button_list.end())
	_current_pos = _button_list.begin();
    }
  if (e.key.code == sf::Keyboard::Up)
    {
      if (_current_pos == _button_list.begin())
	_current_pos = _button_list.end();
      --_current_pos;
    }
  if (e.key.code == sf::Keyboard::Return)
    (*_current_pos).setSelected(true);
  return true;
}

bool	Arcade::SFMLWrapper::renderWindowStart()
{
  sf::Event	e;

  if (_window)
    {
      _window->close();
      delete _window;
    }
  _current_pos = _button_list.begin();
  Arcade::SFMLWrapper::createWindow(1200, 900);
  drawWindow();
  while (_window->isOpen())
    {
      while (_window->pollEvent(e))
	{
	  if (e.type == sf::Event::Closed)
	    _window->close();
	  if (e.type == sf::Event::KeyPressed && keyboardHandler(e))
	    drawWindow();
	}
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
