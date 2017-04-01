//
// NCursesWrapper.hh for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/lib/libncurses/Wrapper
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Wed Mar 29 22:07:36 2017 Victorien Fischer
// Last update Sat Apr  1 20:01:19 2017 Victorien Fischer
//

#ifndef __NCURSESWRAPPER_HH__
# define __NCURSESWRAPPER_HH__

#include <ncurses.h>
#include "IGraphic.hh"
#include "IGame.hh"
#include "ScoreManager.hpp"
#include "StartScreen.hpp"

namespace Arcade
{
  class NCursesWrapper : public Arcade::IGraphic
  {
  public:
    NCursesWrapper();
    ~NCursesWrapper();

  public:
    bool	renderWindowStart();
    void	renderWindowGame(unsigned int, unsigned int, IGame *);
    bool	setPixel(unsigned int, unsigned int, unsigned int);
    LibraryType	getLibraryType() const;
    void	setText(std::string const &to_print, unsigned int y,
			Arcade::ElementPosition const &mode,
			unsigned int fontSize = 15,
			Arcade::Colors const &fontColor = Arcade::Colors::WHITE,
			Arcade::Colors const &backgroundColor = Arcade::Colors::BLACK);
    unsigned int	getDrawableHeight() const;
    unsigned int	getDrawableWidth() const;

  public:
    std::string const	&getLibraryPath() const;
    std::string const	&getGamePath() const;

  private:
    Arcade::StartScreen	_screen;

  private:
    void	drawTitle();
    void       	drawWindow();
    bool	keyboardHandler(unsigned char);
  };
}

#endif
