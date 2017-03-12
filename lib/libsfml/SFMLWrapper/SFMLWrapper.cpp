//
// SFMLWrapper.cpp for arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sat Mar 11 22:36:02 2017 Arnaud WURMEL
// Last update Mon Mar 13 00:08:17 2017 Arnaud WURMEL
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
  _current_pos = _button_list.begin();
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
  if (_library_path.size() == 0)
    text.setString("Choisir une librairie pour lancer le jeu");
  else
    text.setString("Choisir un jeu");
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
  std::vector<Button *>::iterator	it;

  it = _button_list.begin();
  while (it != _button_list.end())
    {
      delete (*it);
      ++it;
    }
  _button_list.clear();
  dir = opendir(_library_path.size() > 0 ? "./games" : "./lib");
  if (dir == NULL)
    {
      std::cerr << "Can't load libraries directory" << std::endl;
      throw std::exception();
    }
  y = 200;
  while ((dent = readdir(dir)))
    {
      if (dent->d_type == DT_REG && std::string(dent->d_name).find(".so") != std::string::npos && y <= 600)
	{
	  _button_list.push_back(new Button(dent->d_name, y, Arcade::Button::CENTER, Arcade::Button::SELECT));
	  _current_pos = --(_button_list.end());
	  y += 30;
	}
    }
  _button_list.push_back(new Button("OK", y + 50, _library_path.size() ? Arcade::Button::RIGHT : Arcade::Button::CENTER, Arcade::Button::VALIDATE, false));
  if (_library_path.size())
    {
      _button_list.push_back(new Button("Annuler", y + 50, Arcade::Button::LEFT, Arcade::Button::RETURN, true));
    }
  closedir(dir);
  _current_pos = _button_list.begin();
}

void	Arcade::SFMLWrapper::drawWindow()
{
  std::vector<Arcade::Button *>::iterator	it;

  _window->clear();
  drawTitle();
  it = _button_list.begin();
  while (it != _button_list.end())
    {
      if (it == _current_pos && !(*it)->isSelected())
	(*it)->draw(*_window, true);
      else
	(*it)->draw(*_window);
      ++it;
    }
  _window->display();
}

bool	Arcade::SFMLWrapper::keyboardHandler(sf::Event const& e)
{
  std::vector<Button *>::iterator	it;

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
    {
      if ((*_current_pos)->getType() == Arcade::Button::SELECT)
	{
	  it = _button_list.begin();
	  while (it != _button_list.end())
	    {
	      if ((*it)->getType() == Arcade::Button::VALIDATE)
		{
		  (*it)->enable(!(*_current_pos)->isSelected());
		}
	      if (it != _current_pos)
		(*it)->setSelected(false);
	      ++it;
	    }
	  (*_current_pos)->setSelected(!(*_current_pos)->isSelected());
	}
      else if ((*_current_pos)->getType() == Arcade::Button::VALIDATE)
	{
	  it = _button_list.begin();
	  while (it != _button_list.end())
	    {
	      if ((*it)->isSelected())
		{
		  if (_library_path.size() == 0)
		    {
		      _library_path = (*it)->getTitle();
		    }
		  else
		    _game_path = (*it)->getTitle();
		  getAllLibrary();
		  return true;
		}
	      ++it;
	    }
	}
      else
	{
	  _library_path.clear();
	  _game_path.clear();
	  getAllLibrary();
	}
    }
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
  getAllLibrary();
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
	  if (_game_path.size() > 0 && _library_path.size() > 0)
	    _window->close();
	}
    }
  std::cout << "Game : " << _game_path << std::endl << "Library : " << _library_path << std::endl;
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
  std::vector<Button *>::iterator	it;

  if (_window)
    delete _window;
  for (it = _button_list.begin(); it != _button_list.end(); it++)
    {
      delete *it;
    }
 
}
