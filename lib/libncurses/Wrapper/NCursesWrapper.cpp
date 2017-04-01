//
// NCursesWrapper.cpp for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/lib/libncurses/Wrapper
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Wed Mar 29 22:19:52 2017 Victorien Fischer
// Last update Sat Apr  1 20:02:37 2017 Victorien Fischer
//

#include <thread>
#include <chrono>
#include "NCursesWrapper.hh"

Arcade::NCursesWrapper::NCursesWrapper()
{
}

bool	Arcade::NCursesWrapper::renderWindowStart()
{
  return (true);
}

void	Arcade::NCursesWrapper::renderWindowGame(unsigned int width, unsigned int height, IGame *game)
{
  char	c;

  initscr();
  nodelay(stdscr, TRUE);
  game->setUpGraphics(this);
  while (42)
    {
      if ((c = getch()))
	{
	  if (c == 27)
	    break;
	  if (c == KEY_UP)
	    game->eventListener(Event(Arcade::Event::AKEY_UP));;
	  if (c == KEY_DOWN)
	    game->eventListener(Event(Arcade::Event::AKEY_DOWN));;
	  if (c == KEY_LEFT)
	    game->eventListener(Event(Arcade::Event::AKEY_LEFT));;
	  if (c == KEY_RIGHT)
	    game->eventListener(Event(Arcade::Event::AKEY_RIGHT));;
	  if (game->gameState() == Arcade::IGame::PLAYING)
	    refresh();
	}
      if (game->shouldRender())
	{
	  erase();
	  game->render();
	  if (game->gameState() == Arcade::IGame::PLAYING)
	    refresh();
	}
      std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
  endwin();
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
}

unsigned int	Arcade::NCursesWrapper::getDrawableHeight() const
{
  return (0);
}

unsigned int	Arcade::NCursesWrapper::getDrawableWidth() const
{
  return (0);
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
  mvprintw((COLS - 3)/2, 2, "Arcade");
  if (_screen.getLibraryPath().size() == 0)
    mvprintw((COLS - 2)/2, 10, "Choisir une bibliothèque pour lancer le jeu");
  else
    mvprintw((COLS - 2)/2, 10, "Choisir un jeu");
}

void	Arcade::NCursesWrapper::drawWindow()
{
  erase();
  drawTitle();
  _screen.render(this);
  refresh();
}

bool	Arcade::NCursesWrapper::keyboardHandler(unsigned char e)
{
  if (e == 27)
    {
      endwin();
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
