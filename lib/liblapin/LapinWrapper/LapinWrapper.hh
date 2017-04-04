//
// LapinWrapper.hh for cpp_arcade in /home/wurmel_a/rendu/cpp_arcade/lib/libopengl
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Mon Apr  3 22:01:33 2017 Arnaud WURMEL
// Last update Tue Apr  4 12:55:26 2017 Arnaud WURMEL
//

#ifndef LAPINWRAPPER_HH_
# define LAPINWRAPPER_HH_

# include "lapin.h"
# include "IGraphic.hh"
# include "IGame.hh"
# include "ScoreManager.hpp"
# include "StartScreen.hpp"

namespace Arcade
{
  class	LapinWrapper : public Arcade::IGraphic
  {
  public:
    LapinWrapper();
    ~LapinWrapper();

  public:
    bool	renderWindowStart();
    void	renderWindowGame(unsigned int, unsigned int, IGame*);
    bool	setPixel(unsigned int, unsigned int, unsigned int);
    LibraryType	getLibraryType() const;
    void	setText(std::string const&to_print, unsigned int y,
			Arcade::ElementPosition const& mode,
			unsigned int fontSize = 15,
			Arcade::Colors const& fontColor = Arcade::Colors::AWHITE,
			Arcade::Colors const& backgroundColor = Arcade::Colors::ABLACK);
    unsigned int	getDrawableHeight() const;
    unsigned int	getDrawableWidth() const;

  private:
    bool	createWindow(unsigned int, unsigned int);
    t_bunny_pixelarray	*createPixelArray(unsigned int, unsigned int);

  public:
    std::string const&	getLibraryPath() const;
    std::string const&	getGamePath() const;
    std::string const&	getPseudo() const;

  public:
    Arcade::StartScreen	_screen;
    t_bunny_window	*_window;
    t_bunny_pixelarray	*_root;

  private:
    t_bunny_pixelarray	*_font;

  private:
    std::string		_library_path;
    std::string		_game_path;
    std::string		_pseudo;
  };
}

#endif /* !OPENGLWRAPPER_HH_ */
