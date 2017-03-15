//
// SFMLWrapper.cpp for arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sat Mar 11 22:36:02 2017 Arnaud WURMEL
// Last update Wed Mar 15 18:08:07 2017 Arnaud WURMEL
//

#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <chrono>
#include <thread>
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
    text.setString("Choisir une bibliotheque pour lancer le jeu");
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
    _button_list.push_back(new Button("Annuler", y + 50, Arcade::Button::LEFT, Arcade::Button::RETURN, true));
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
  getScore();
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
	    {
	      _window->close();
	      return false;
	    }
	  if (e.type == sf::Event::KeyPressed && keyboardHandler(e))
	    drawWindow();
	  if (_game_path.size() > 0 && _library_path.size() > 0)
	    _window->close();
	}
    }
  return _library_path.size() && _game_path.size();
}

bool	Arcade::SFMLWrapper::createWindow(unsigned int width, unsigned int height)
{
  _window = new sf::RenderWindow(sf::VideoMode(width, height), "SFMLWrapper", sf::Style::Close);
  return true;
}

bool	Arcade::SFMLWrapper::setPixel(unsigned int x, unsigned int y,
				      unsigned int color)
{
  sf::Color	colors[7];

  colors[BLACK] = sf::Color::Black;
  colors[GREEN] = sf::Color(39, 174, 96);
  colors[GREY] = sf::Color(52, 73, 94);
  colors[CYAN] = sf::Color(52, 152, 219);
  colors[YELLOW] = sf::Color(241, 196, 15);
  colors[RED] = sf::Color(231, 76, 60);
  colors[PINK] = sf::Color(142, 68, 173);
  if (x >= _image.getSize().x ||
      y >= _image.getSize().x)
    return false;
  _image.setPixel(x, y, colors[color % 6]);
  return true;
}

Arcade::LibraryType	Arcade::SFMLWrapper::getLibraryType() const
{
  return (Arcade::GRAPHIC);
}

std::string const&	Arcade::SFMLWrapper::getLibraryPath() const
{
  return (_library_path);  
}

std::string const&	Arcade::SFMLWrapper::getGamePath() const
{
  return (_game_path);
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
		game->eventListener(Event(Arcade::Event::KEY_UP));
	      else if (e.key.code == sf::Keyboard::Down)
		game->eventListener(Event(Arcade::Event::KEY_DOWN));
	      else if (e.key.code == sf::Keyboard::Left)
		game->eventListener(Event(Arcade::Event::KEY_LEFT));
	      else if (e.key.code == sf::Keyboard::Right)
		game->eventListener(Event(Arcade::Event::KEY_RIGHT));
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
      std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

void	Arcade::SFMLWrapper::setText(std::string const& to_print, unsigned int y,
				     Arcade::TextMode const& mode, unsigned int fontSize)
{
  sf::Text	text;
  sf::Font	font;
  unsigned int	x;

  if (!font.loadFromFile("Ressources/font.ttf"))
    std::cerr << "Can't load font.ttf" << std::endl;
  else
    text.setFont(font);
  text.setString(to_print);
  text.setCharacterSize(fontSize);
  x = 5;
  if (mode == Arcade::TextMode::CENTER)
    x = (_window->getView().getSize().x / 2 - (text.getLocalBounds().width / 2));
  else if (mode == Arcade::TextMode::RIGHT)
    x = ((_window->getView().getSize().x - text.getLocalBounds().width) - 5);
  text.setPosition(x, y);
  text.setColor(sf::Color::White);
  _window->draw(text);
}

void	Arcade::SFMLWrapper::getScore()
{
  Arcade::ScoreManager	scoreManager;
  std::string	text_line;
  size_t	pos;

  if (_library_path.size() && !_game_path.size())
    {
      if ((*_current_pos)->getType() == Arcade::Button::SELECT)
	{
	  std::string game_name = (*_current_pos)->getTitle();
	  
	  if (game_name.find("lib_arcade_") == 0)
	    game_name.erase(0, 11);
	  if ((pos = game_name.find(".so")) != std::string::npos)
	    game_name.erase(pos);
	  std::vector<Arcade::ScoreManager::ScoreRow> const&	vec = scoreManager.getScoreForGame(game_name);
	  std::vector<Arcade::ScoreManager::ScoreRow>::const_iterator	it;

	  it = vec.begin();
	  pos = 600;
	  for (unsigned int i = 0; i < 10 && it != vec.end(); i++) {
	    text_line = "#" + std::to_string(i + 1) + " ";
	    text_line = text_line + (*it).pseudo + " : " + std::to_string((*it).score);
	    setText(text_line, 250 + ((_button_list.size() + 1) * 32) + (i * 20), Arcade::TextMode::CENTER);
	    ++it;
	  }
	}
    }
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
  std::vector<Button *>::iterator	it;

  if (_window)
    delete _window;
  for (it = _button_list.begin(); it != _button_list.end(); it++)
    {
      delete *it;
    }
}
