//
// NCursesWrapper.cpp for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/lib/libncurses/Wrapper
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Wed Mar 29 22:19:52 2017 Victorien Fischer
// Last update Thu Mar 30 15:41:43 2017 Victorien Fischer
//

#include <thread>
#include <chrono>
#include "NCursesWrapper.hh"

Arcade::NCursesWrapper::NCursesWrapper()
{
}

Arcade::LibraryType	Arcade::NCursesWrapper::getLibraryType() const
{
  return (Arcade::GRAPHIC);
}

std::string const	&Arcade::NCursesWrapper::getLibraryPath() const
{
  return (_screen.getLibraryPath());
}

std::string const	&Arcade::NCursesWrapper::getGamePath() const
{
  return (_screen.getGamePath());
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
	printf("got %c\n", c);
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
