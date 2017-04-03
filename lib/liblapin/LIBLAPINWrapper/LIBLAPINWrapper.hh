//
// LIBLAPINWrapper.hpp for arcade in /home/ballet/CPP/cpp_arcade/lib/liblapin/LIBLAPINWrapper/
//
// Made by Ballet Erwan
// Login   <erwan.ballet@epitech.eu>
//
// Started on  Sun Mar 12 07:18:50 2017 Ballet Erwan
// Last update Mon Apr  3 13:22:01 2017 Ballet Erwan
//

#ifndef LIBLAPINWRAPPER_HH_
# define LIBLAPINWRAPPER_HH_

# include "Button.hh"
# include "IGraphic.hh"
# include "IGame.hh"
# include "ScoreManager.hpp"
# include "StartScreen.hpp"
# include "lapin.h"

namespace Arcade
{
  class	LIBLAPINWrapper : public Arcade::IGraphic
  {
  public:
    LIBLAPINWrapper();
    ~LIBLAPINWrapper();
  public:
    bool	renderWindowStart();
    void	renderWindowGame(unsigned int, unsigned int, IGame *);
    bool	setPixel(unsigned int x, unsigned int y, unsigned int color);
    LibraryType	getLibraryType() const;
    void	setText(std::string const&, unsigned int y,
        Arcade::ElementPosition const&,
        unsigned int fontSize,
        Arcade::Colors const& fontColor,
        Arcade::Colors const& backgroundColor);
    unsigned int	getDrawableHeight() const;
    unsigned int	getDrawableWidth() const;

  public:
    std::string const&	getGamePath() const;
    std::string const&	getLibraryPath() const;

  private:
    t_bunny_window  *_win;
    Arcade::StartScreen		_screen;
  };
}

#endif /* !LIBLAPINWRAPPER_HH_ */
