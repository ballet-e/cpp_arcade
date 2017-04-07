//
// NCursesWrapper.hh for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/lib/libncurses/Wrapper
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Wed Mar 29 22:07:36 2017 Victorien Fischer
// Last update Fri Apr  7 23:38:02 2017 Arnaud WURMEL
//

#ifndef __NCURSESWRAPPER_HH__
# define __NCURSESWRAPPER_HH__

# include <map>
# include <utility>
# include <ncurses.h>
# include <memory>
# include "IGraphic.hh"
# include "IGame.hh"
# include "ScoreManager.hpp"
# include "StartScreen.hpp"
# include "Event.hh"
# include "Text.hh"

namespace Arcade
{
  class NCursesWrapper : public Arcade::IGraphic
  {
  public:
    NCursesWrapper();
    ~NCursesWrapper();

  public:
    bool	renderWindowStart();
    Arcade::ExitStatus	renderWindowGame(unsigned int, unsigned int, IGame *);
    bool	setPixel(unsigned int, unsigned int, unsigned int);
    LibraryType	getLibraryType() const;
    void	setText(std::string const &to_print, unsigned int y,
			Arcade::ElementPosition const &mode,
			unsigned int fontSize = 15,
			Arcade::Colors const &fontColor = Arcade::Colors::AWHITE,
			Arcade::Colors const &backgroundColor = Arcade::Colors::ABLACK);
    unsigned int	getDrawableHeight() const;
    unsigned int	getDrawableWidth() const;

  public:
    std::string const	&getLibraryPath() const;
    std::string const	&getGamePath() const;
    std::string const	&getPseudo() const;

  public:
    static bool	sortTextVector(std::unique_ptr<Arcade::Text> const&, std::unique_ptr<Arcade::Text> const&);

  private:
    void	drawTitle();
    void       	drawWindow();
    bool	keyboardHandler(int);
    bool	createWindow();
    bool	deleteWindow();
    short	createPair(short, short);
    void	drawText();

  private:
    Arcade::IGame	*_game;
    Arcade::StartScreen	_screen;
    WINDOW		*_window;
    std::vector<std::unique_ptr<Arcade::Text>>	_text;
    std::map<short, std::pair<short, short>>	_colorpair;
    std::map<char, Arcade::ExitStatus>	_mapping;
    std::map<unsigned int, Arcade::Event::EventType>	_keyEvent;
  };
}

#endif
