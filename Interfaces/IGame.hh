//
// IGame.hh for arcade in /home/wurmel/rendu/cpp_arcade
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Mon Mar 13 10:47:40 2017 Arnaud WURMEL
// Last update Mon Mar 13 17:26:50 2017 Arnaud WURMEL
//

#ifndef IGAME_HH_
# define IGAME_HH_

# include "ILibrary.hh"

namespace	Arcade
{
  class	IGraphic;

  class	IGame : public Arcade::ILibrary
  {
  public:
    virtual void	setUpGraphics(Arcade::IGraphic *) = 0;
    virtual ~IGame() {}
  };
}

#endif /* !IGAME_HH_ */
