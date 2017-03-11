//
// IGraphic.hh for arcade in /home/wurmel/rendu/cpp_arcade
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sat Mar 11 11:29:38 2017 Arnaud WURMEL
// Last update Sat Mar 11 23:32:08 2017 Arnaud WURMEL
//

#ifndef IGRAPHIC_HH_
# define IGRAPHIC_HH_

# include "ILibrary.hh"

namespace Arcade
{
  class	IGraphic : public Arcade::ILibrary
  {
  public:
    virtual ~IGraphic() {}
    virtual bool	renderWindowStart() = 0;
    virtual bool	drawSquare64x64(unsigned int x, unsigned int y, unsigned int color) = 0;
    virtual bool	createWindow(unsigned int, unsigned int) = 0;
  };
}

#endif /* !IGRAPHIC_HH_ */
