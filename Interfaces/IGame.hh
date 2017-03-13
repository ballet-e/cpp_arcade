//
// IGame.hh for arcade in /home/wurmel/rendu/cpp_arcade
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Mon Mar 13 10:47:40 2017 Arnaud WURMEL
// Last update Mon Mar 13 16:31:01 2017 Arnaud WURMEL
//

#ifndef IGAME_HH_
# define IGAME_HH_

# include "ILibrary.hh"

class	IGraphic;

namespace	Arcade
{
  class	IGame : public Arcade::ILibrary
  {
  public:
    virtual void	setUpGraphics(IGraphic *) = 0;
    virtual ~IGame() {}
  };
}

#endif /* !IGAME_HH_ */
