//
// IGraphic.hh for arcade in /home/wurmel/rendu/cpp_arcade
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sat Mar 11 11:29:38 2017 Arnaud WURMEL
// Last update Thu Mar 16 00:52:12 2017 Arnaud WURMEL
//

#ifndef IGRAPHIC_HH_
# define IGRAPHIC_HH_

# include <string>
# include "ILibrary.hh"
# include "IGame.hh"

namespace Arcade
{
  enum	Colors
    {
      BLACK = 0,
      GREY,
      CYAN,
      GREEN,
      YELLOW,
      RED,
      PINK,
      WHITE
    };
  enum	ElementPosition
    {
      CENTER,
      LEFT,
      RIGHT,
      LEFT_CENTER,
      RIGHT_CENTER
    };
  class	IGraphic : public Arcade::ILibrary
  {
  public:
    virtual ~IGraphic() {}
    virtual bool	renderWindowStart() = 0;
    virtual void	renderWindowGame(unsigned int, unsigned int, IGame *) = 0;
    virtual bool	setPixel(unsigned int x, unsigned int y, unsigned int color) = 0;
    virtual void	setText(std::string const&, unsigned int y,
				Arcade::ElementPosition const&,
				unsigned int fontSize = 15,
				Arcade::Colors const& fontColor = Arcade::Colors::WHITE,
				Arcade::Colors const& backgroundColor = Arcade::Colors::BLACK) = 0;
    virtual unsigned int	getDrawableHeight() const = 0;
    virtual unsigned int	getDrawableWidth() const = 0;

  public:
    virtual std::string const&	getGamePath() const = 0;
    virtual std::string const&	getLibraryPath() const = 0;
  };
}

#endif /* !IGRAPHIC_HH_ */
