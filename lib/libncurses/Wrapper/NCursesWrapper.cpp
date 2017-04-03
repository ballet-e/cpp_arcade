//
// NCursesWrapper.cpp for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/lib/libncurses/Wrapper
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Wed Mar 29 22:19:52 2017 Victorien Fischer
// Last update Mon Apr  3 16:35:17 2017 Victorien Fischer
//

#include <thread>
#include <chrono>
#include "NCursesWrapper.hh"

Arcade::NCursesWrapper::NCursesWrapper()
{
  initscr();
  cbreak();
  noecho();
  start_color();
  init_color(BLACK, 0, 0, 0);
  init_color(GREEN, 39, 174, 96);
  init_color(GREY, 120, 120, 120);
  init_color(CYAN, 52, 152, 219);
  init_color(YELLOW, 241, 196, 15);
  init_color(RED, 231, 76, 60);
  init_color(PINK, 231, 76, 60);
  init_color(WHITE, 255, 255, 255);
  _row = 0;
  _col = 0;
  _window = NULL;
}

bool	Arcade::NCursesWrapper::renderWindowStart()
{
  int	key;

  deleteWindow();
  createWindow(80, 80);
  drawWindow();
  while (_window)
    {
      if ((key = wgetch(_window)) != ERR)
	{
	  if (keyboardHandler(key))
	    drawWindow();
	  if (_screen.getGamePath().size() > 0 &&
	      _screen.getLibraryPath().size() > 0)
	    {
	      delwin(_window);
	      _window = NULL;
	    }
	}
      //std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  return (_screen.getLibraryPath().size() && _screen.getGamePath().size());
}

void	Arcade::NCursesWrapper::renderWindowGame(unsigned int width, unsigned int height, IGame *game)
{
  int	key;

  deleteWindow();
  createWindow(width, height);
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
	  if (game->gameState() == Arcade::IGame::PLAYING)
	    wrefresh(_window);
	}
      if (game->shouldRender())
	{
	  wclear(_window);
	  game->render();
	  if (game->gameState() == Arcade::IGame::PLAYING)
	    wrefresh(_window);
	}
      std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

bool	Arcade::NCursesWrapper::setPixel(unsigned int x, unsigned int y, unsigned int p)
{
  return (true);
}

Arcade::LibraryType	Arcade::NCursesWrapper::getLibraryType() const
{
  return (Arcade::GRAPHIC);
}

void	Arcade::NCursesWrapper::setText(std::string const &to_print,
					unsigned int y,
					Arcade::ElementPosition const &mode,
					unsigned int fontSize,
					Arcade::Colors const &fontColor,
					Arcade::Colors const &backgroundColor)
{
  init_pair(1, fontColor, backgroundColor);
  wmove(_window, (y / 12), (_row - to_print.length())/2);
  wattron(_window, COLOR_PAIR(1));
  wprintw(_window, to_print.c_str());
  wattroff(_window, COLOR_PAIR(1));
}

unsigned int	Arcade::NCursesWrapper::getDrawableHeight() const
{
  return (_row);
}

unsigned int	Arcade::NCursesWrapper::getDrawableWidth() const
{
  return (_col);
}

std::string const	&Arcade::NCursesWrapper::getLibraryPath() const
{
  return (_screen.getLibraryPath());
}

std::string const	&Arcade::NCursesWrapper::getGamePath() const
{
  return (_screen.getGamePath());
}

void	Arcade::NCursesWrapper::drawTitle()
{
  std::string	name("Arcade");
  std::string	lib("Choisir une bibliothèque pour lancer le jeu");
  std::string	game("Choisir un jeu");
  
  mvwprintw(_window, 4, (_row - name.length())/2, name.c_str());
  if (_screen.getLibraryPath().size() == 0)
    mvwprintw(_window, 7, (_row - lib.length())/2, lib.c_str());
  else
    mvwprintw(_window, 7, (_row - game.length())/2, game.c_str());
}

bool	Arcade::NCursesWrapper::createWindow(unsigned int width, unsigned int height)
{
  _row = width;
  _col = height;
  resizeterm(_row, _col);
  _window = newwin(width, height, 0, 0);
  nodelay(_window, TRUE);
  keypad(_window, TRUE);
}

bool	Arcade::NCursesWrapper::deleteWindow()
{
  if (_window)
    {
      delwin(_window);
      _window = NULL;
      return (true);
    }
  return (false);
}

void	Arcade::NCursesWrapper::drawWindow()
{
  wclear(_window);
  drawTitle();
  _screen.render(this);
  wrefresh(_window);
}

bool	Arcade::NCursesWrapper::keyboardHandler(int e)
{
  if (e == 27)
    {
      deleteWindow();
      _window = NULL;
      return (false);
    }
  if (e == KEY_ENTER)
    _screen.enterKey();
  if (e == KEY_UP)
    _screen.upKey();
  if (e == KEY_DOWN)
    _screen.downKey();
  return (true);
}

Arcade::NCursesWrapper::~NCursesWrapper()
{
  endwin();
}
