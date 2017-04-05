//
// NCursesWrapper.cpp for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/lib/libncurses/Wrapper
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Wed Mar 29 22:19:52 2017 Victorien Fischer
// Last update Thu Apr  6 00:23:43 2017 Arnaud WURMEL
//

#include <thread>
#include <algorithm>
#include <chrono>
#include "NCursesWrapper.hh"

Arcade::NCursesWrapper::NCursesWrapper()
{
  _window = NULL;
}

bool	Arcade::NCursesWrapper::renderWindowStart()
{
  int	key;

  deleteWindow();
  createWindow();
  drawWindow();
  while (_window)
    {
      if ((key = wgetch(_window)) != ERR)
	{
	  if (keyboardHandler(key))
	    drawWindow();
	  if (_screen.getGamePath().size() > 0 &&
	      _screen.getLibraryPath().size() > 0)
	    deleteWindow();
	}
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  return (_screen.getLibraryPath().size() && _screen.getGamePath().size());
}

void	Arcade::NCursesWrapper::renderWindowGame(unsigned int width, unsigned int height,
						 IGame *game)
{
  int	key;

  static_cast<void>(width);
  static_cast<void>(height);
  deleteWindow();
  createWindow();
  game->setUpGraphics(this);
  while (_window)
    {
      if ((key = wgetch(_window)) != ERR)
	{
	  if (key == 27)
	    {
	      deleteWindow();
	      return ;
	    }
	  if (key == KEY_UP)
	    game->eventListener(Event(Arcade::Event::AKEY_UP));;
	  if (key == KEY_DOWN)
	    game->eventListener(Event(Arcade::Event::AKEY_DOWN));;
	  if (key == KEY_LEFT)
	    game->eventListener(Event(Arcade::Event::AKEY_LEFT));;
	  if (key == KEY_RIGHT)
	    game->eventListener(Event(Arcade::Event::AKEY_RIGHT));;
	}
      if (game->shouldRender())
	{
	  wclear(_window);
	  _text.clear();
	  game->render();
	  drawText();
	  if (game->gameState() == Arcade::IGame::PLAYING)
	    wrefresh(_window);
	}
      std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

bool	Arcade::NCursesWrapper::setPixel(unsigned int x, unsigned int y, unsigned int color)
{
  short	id_pair;
  int	x_pos;
  int	y_pos;

  std::cerr << color << std::endl;
  id_pair = createPair(color + 8, color + 8);
  if (x >= getDrawableWidth() || y >= getDrawableHeight())
    return (false);
  wattron(_window, COLOR_PAIR(id_pair));
  x_pos = (COLS - (getDrawableWidth() * 2)) / 2;
  x_pos += (x * 2);
  y_pos = (LINES - getDrawableHeight()) / 2;
  y_pos += y;
  if (y_pos < LINES && y_pos >= 0 && x_pos < COLS && x_pos >= 0)
    mvwprintw(_window, y_pos, x_pos, "xx");
  wattroff(_window, COLOR_PAIR(id_pair));
  return (true);
}

Arcade::LibraryType	Arcade::NCursesWrapper::getLibraryType() const
{
  return (Arcade::GRAPHIC);
}

void	Arcade::NCursesWrapper::drawText()
{
  unsigned int	i;
  int	id_pair;
  unsigned int	line;

  std::sort(_text.begin(), _text.end(), Arcade::NCursesWrapper::sortTextVector);
  line = 1;
  i = 0;
  while (i < _text.size())
    {
      id_pair = createPair(_text[i]->getFont() + 8, _text[i]->getBack() + 8);
      if (i > 0)
	{
	  if (_text[i]->getY() - _text[i - 1]->getY() >= 40)
	    line += 1;
	}
      wmove(_window, line, _text[i]->getX());
      wattron(_window, COLOR_PAIR(id_pair));
      wprintw(_window, _text[i]->getText().c_str());
      wattroff(_window, COLOR_PAIR(id_pair));
      refresh();
      wrefresh(_window);
      ++i;
      if (i > 0 && i < _text.size() && _text[i]->getY() == _text[i - 1]->getY())
	line -= 1;
      line += 1;
    }
}

bool	Arcade::NCursesWrapper::sortTextVector(std::unique_ptr<Arcade::Text> const& first,
					       std::unique_ptr<Arcade::Text> const& second)
{
  return first->getY() < second->getY();
}

void	Arcade::NCursesWrapper::setText(std::string const &to_print,
					unsigned int y,
					Arcade::ElementPosition const &mode,
					unsigned int fontSize,
					Arcade::Colors const &fontColor,
					Arcade::Colors const &backgroundColor)
{
  unsigned int	x;

  static_cast<void>(fontSize);
  x = 1;
  if (mode == Arcade::ElementPosition::CENTER)
    x = (COLS - to_print.size()) / 2;
  else if (mode == Arcade::ElementPosition::RIGHT)
    x = (COLS - to_print.size() - 1);
  else if (mode == Arcade::ElementPosition::RIGHT_CENTER)
    x = (COLS / 2) + 2;
  else if (mode == Arcade::ElementPosition::LEFT_CENTER)
    x = (COLS / 2) - (to_print.size() + 2);
  _text.push_back(std::unique_ptr<Arcade::Text>(new Arcade::Text(to_print, x, y, fontColor, backgroundColor)));
}

short		Arcade::NCursesWrapper::createPair(short font,
						   short back)
{
  short		id;
  std::map<short, std::pair<short, short>>::iterator	it;

  id = 1;
  it = _colorpair.begin();
  while (it != _colorpair.end())
    {
      id += 1;
      if ((it->second).first == font && (it->second).second == back)
	return (it->first);
      it++;
    }
  init_pair(id, font, back);
  _colorpair.insert(std::pair<short, std::pair<short, short>>
		    (id, std::pair<short, short>(font, back)));
  return (id);
}

unsigned int	Arcade::NCursesWrapper::getDrawableHeight() const
{
  return 20;
}

unsigned int	Arcade::NCursesWrapper::getDrawableWidth() const
{
  return 20;
}

std::string const	&Arcade::NCursesWrapper::getLibraryPath() const
{
  return (_screen.getLibraryPath());
}

std::string const	&Arcade::NCursesWrapper::getGamePath() const
{
  return (_screen.getGamePath());
}

std::string const	&Arcade::NCursesWrapper::getPseudo() const
{
  return (_screen.getPseudo());
}

void	Arcade::NCursesWrapper::drawTitle()
{
  std::string	name("Arcade");
  std::string	lib("Choisir une bibliothèque pour lancer le jeu");
  std::string	game("Choisir un jeu");
  std::string	pseudo("Entrez votre pseudo");

  setText(name, 0, Arcade::ElementPosition::CENTER);
  if (_screen.getLibraryPath().size() == 0)
    setText(lib, 50, Arcade::ElementPosition::CENTER);
  else if (_screen.getGamePath().size() == 0)
    setText(game, 50, Arcade::ElementPosition::CENTER);
  else
    setText(pseudo, 50, Arcade::ElementPosition::CENTER);
}

bool	Arcade::NCursesWrapper::createWindow()
{
  initscr();
  start_color();
  cbreak();
  noecho();
  _window = newwin(0, 0, 0, 0);
  nodelay(_window, TRUE);
  keypad(_window, TRUE);
  init_color(ABLACK + 8, 0, 0, 0);
  init_color(AGREY + 8, 120, 180, 10);
  init_color(AGREEN + 8, 39, 174, 96);
  init_color(ACYAN + 8, 52, 152, 219);
  init_color(AYELLOW + 8, 241, 196, 15);
  init_color(ARED + 8, 231, 76, 60);
  init_color(APINK + 8, 231, 76, 60);
  init_color(AWHITE + 8, 255, 255, 255);
  return (true);
}

bool	Arcade::NCursesWrapper::deleteWindow()
{
  if (_window)
    {
      delwin(_window);
      endwin();
      _window = NULL;
      return (true);
    }
  return (false);
}

void	Arcade::NCursesWrapper::drawWindow()
{
  wclear(_window);
  _text.clear();
  drawTitle();
  _screen.render(this);
  drawText();
  wrefresh(_window);
}

bool	Arcade::NCursesWrapper::keyboardHandler(int e)
{
  if (e == 27)
    {
      deleteWindow();
      return (false);
    }
  if (e == 10)
    _screen.enterKey();
  if (e == KEY_UP)
    _screen.upKey();
  if (e == KEY_DOWN)
    _screen.downKey();
  return (true);
}

Arcade::NCursesWrapper::~NCursesWrapper()
{

}
