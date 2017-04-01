//
// SFMLWrapper.cpp for arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sat Mar 11 22:36:02 2017 Arnaud WURMEL
// Last update Sat Apr  1 19:51:29 2017 Arnaud WURMEL
//

#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <exception>
#include "SFMLWrapper.hh"
#include "StartScreen.hpp"

Arcade::SFMLWrapper::SFMLWrapper()
{
  _window = NULL;
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
  if (_screen.getLibraryPath().size() == 0)
    text.setString("Choisir une bibliotheque pour lancer le jeu");
  else
    text.setString("Choisir un jeu");
  text.setCharacterSize(15);
  text.setColor(sf::Color::White);
  text.setPosition(600 - (text.getLocalBounds().width / 2), 120);
  _window->draw(text);
}

void	Arcade::SFMLWrapper::drawWindow()
{
  _window->clear();
  drawTitle();
  _screen.render(this);
  _window->display();
}

bool	Arcade::SFMLWrapper::keyboardHandler(sf::Event const& e)
{
  if (e.key.code == sf::Keyboard::Escape)
    {
      _window->close();
      return false;
    }
  if (e.key.code == sf::Keyboard::Return)
    _screen.enterKey();
  if (e.key.code == sf::Keyboard::Up)
    _screen.upKey();
  if (e.key.code == sf::Keyboard::Down)
    _screen.downKey();
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
  Arcade::SFMLWrapper::createWindow(1200, 900);
  drawWindow();
  while (_window->isOpen())
    {
      while (_window->pollEvent(e))
	{
	  if (e.type == sf::Event::Closed)
	    {
	      _window->close();
	      return false;
	    }
	  if (e.type == sf::Event::KeyPressed && keyboardHandler(e))
	    drawWindow();
	  if (_screen.getGamePath().size() > 0 && _screen.getLibraryPath().size() > 0)
	    _window->close();
	}
    }
  return _screen.getLibraryPath().size() && _screen.getGamePath().size();
}

bool	Arcade::SFMLWrapper::createWindow(unsigned int width, unsigned int height)
{
  _window = new sf::RenderWindow(sf::VideoMode(width, height), "SFMLWrapper", sf::Style::Close);
  return true;
}

bool	Arcade::SFMLWrapper::setPixel(unsigned int x, unsigned int y,
				      unsigned int color)
{
  sf::Color	colors[8];

  getColor(colors);
  if (x >= _image.getSize().x ||
      y >= _image.getSize().x)
    return false;
  _image.setPixel(x, y, colors[color % 8]);
  return true;
}

Arcade::LibraryType	Arcade::SFMLWrapper::getLibraryType() const
{
  return (Arcade::GRAPHIC);
}

std::string const&	Arcade::SFMLWrapper::getLibraryPath() const
{
  return _screen.getLibraryPath();
}

std::string const&	Arcade::SFMLWrapper::getGamePath() const
{
  return _screen.getGamePath();
}

void	Arcade::SFMLWrapper::renderGame()
{
  sf::Texture	texture;
  sf::Sprite	sprite;

  texture.loadFromImage(_image);
  sprite.setTexture(texture, true);
  sprite.setPosition((_window->getView().getSize().x - 600) / 2, 100);
  _window->draw(sprite);
}

void	Arcade::SFMLWrapper::renderWindowGame(unsigned int width, unsigned int height, IGame* game)
{
  sf::Event	e;

  if (_window)
    {
      _window->close();
      delete _window;
    }
  createWindow(width, height);
  _image.create(600, 600);
  game->setUpGraphics(this);
  while (_window->isOpen())
    {
      if (_window->pollEvent(e))
	{
	  if (e.type == sf::Event::Closed ||
	      (e.type == sf::Event::KeyPressed &&
	       e.key.code == sf::Keyboard::Escape))
	    {
	      _window->close();
	      return ;
	    }
	  if (e.type == sf::Event::KeyPressed)
	    {
	      if (e.key.code == sf::Keyboard::Up)
		game->eventListener(Event(Arcade::Event::AKEY_UP));
	      else if (e.key.code == sf::Keyboard::Down)
		game->eventListener(Event(Arcade::Event::AKEY_DOWN));
	      else if (e.key.code == sf::Keyboard::Left)
		game->eventListener(Event(Arcade::Event::AKEY_LEFT));
	      else if (e.key.code == sf::Keyboard::Right)
		game->eventListener(Event(Arcade::Event::AKEY_RIGHT));
	    }
	  if (game->gameState() == Arcade::IGame::PLAYING)
	    renderGame();
	}
      if (game->shouldRender())
	{
 	  _window->clear();
	  game->render();
	  if (game->gameState() == Arcade::IGame::PLAYING)
	    renderGame();
	}
      _window->display();
      std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
}

void	Arcade::SFMLWrapper::getColor(sf::Color colors[8]) const
{
  colors[BLACK] = sf::Color::Black;
  colors[GREEN] = sf::Color(39, 174, 96);
  colors[GREY] = sf::Color(120, 120, 120);
  colors[CYAN] = sf::Color(52, 152, 219);
  colors[YELLOW] = sf::Color(241, 196, 15);
  colors[RED] = sf::Color(231, 76, 60);
  colors[PINK] = sf::Color(142, 68, 173);
  colors[WHITE] = sf::Color(255, 255, 255);
}

void	Arcade::SFMLWrapper::setText(std::string const& to_print,
				     unsigned int y,
				     Arcade::ElementPosition const& mode,
				     unsigned int fontSize,
				     Arcade::Colors const& fontColor,
				     Arcade::Colors const& backgroundColor)
{
  sf::Text	text;
  sf::Font	font;
  sf::Color	colors[8];
  unsigned int	x;

  if (!font.loadFromFile("Ressources/font.ttf"))
    std::cerr << "Can't load font.ttf" << std::endl;
  else
    text.setFont(font);
  text.setString(to_print);
  text.setCharacterSize(fontSize);
  x = 5;
  getColor(colors);
  if (mode == Arcade::ElementPosition::CENTER)
    x = (_window->getView().getSize().x / 2 - (text.getLocalBounds().width / 2));
  else if (mode == Arcade::ElementPosition::RIGHT)
    x = ((_window->getView().getSize().x - text.getLocalBounds().width) - 5);
  else if (mode == Arcade::ElementPosition::RIGHT_CENTER)
    x = ((_window->getView().getSize().x / 2) + 50);
  else if (mode == LEFT_CENTER)
    x = ((_window->getView().getSize().x / 2) - (text.getLocalBounds().width + 50));
  text.setPosition(x, y);
  text.setColor(colors[fontColor]);
  sf::FloatRect backgroundRect = text.getLocalBounds();
  sf::RectangleShape background(sf::Vector2f(backgroundRect.width + 4, backgroundRect.height + 4));

  background.setFillColor(colors[backgroundColor]);
  background.setPosition(x - 2, y);
  _window->draw(background);
  _window->draw(text);
}

unsigned int	Arcade::SFMLWrapper::getDrawableHeight() const
{
  return _image.getSize().y;
}

unsigned int	Arcade::SFMLWrapper::getDrawableWidth() const
{
  return _image.getSize().x;
}

Arcade::SFMLWrapper::~SFMLWrapper()
{

}
