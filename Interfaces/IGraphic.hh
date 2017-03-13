//
// IGraphic.hh for arcade in /home/wurmel/rendu/cpp_arcade
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sat Mar 11 11:29:38 2017 Arnaud WURMEL
// Last update Mon Mar 13 17:39:17 2017 Arnaud WURMEL
//

#ifndef IGRAPHIC_HH_
# define IGRAPHIC_HH_

# include <string>
# include "ILibrary.hh"
# include "IGame.hh"

namespace Arcade
{
  enum	TextMode
    {
      LEFT,
      CENTER,
      RIGHT
    };
  class	IGraphic : public Arcade::ILibrary
  {
  public:
    virtual ~IGraphic() {}
    virtual bool	renderWindowStart() = 0;
    virtual void	renderWindowGame(unsigned int, unsigned int, IGame*) = 0;
    virtual bool	setPixel(unsigned int x, unsigned int y, unsigned int color) = 0;
    virtual void	setText(std::string const&, unsigned int y, TextMode const&) = 0;

  public:
    virtual std::string const&	getGamePath() const = 0;
    virtual std::string const&	getLibraryPath() const = 0;
  };
}

#endif /* !IGRAPHIC_HH_ */
