//
// IGraphic.hh for arcade in /home/wurmel/rendu/cpp_arcade
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sat Mar 11 11:29:38 2017 Arnaud WURMEL
// Last update Sat Mar 11 11:33:20 2017 Arnaud WURMEL
//

#ifndef IGRAPHIC_HH_
# define IGRAPHIC_HH_


namespace Arcade
{
  class	IGraphic
  {
  public:
    bool	renderWindowStart() = 0;
    bool	drawSquare64x64(unsigned int x, unsigned int y, unsigned int color) = 0;
  };
}

#endif /* !IGRAPHIC_HH_ */
