//
// IGame.hh for arcade in /home/wurmel/rendu/cpp_arcade
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Mon Mar 13 10:47:40 2017 Arnaud WURMEL
// Last update Mon Mar 13 22:02:34 2017 Arnaud WURMEL
//

#ifndef IGAME_HH_
# define IGAME_HH_

# include "ILibrary.hh"
# include "Event.hh"

namespace	Arcade
{
  class	IGraphic;

  class	IGame : public Arcade::ILibrary
  {
  public:
    virtual void	setUpGraphics(Arcade::IGraphic *) = 0;
    virtual void	eventListener(Event const&) = 0;
    virtual void	render() = 0;
    virtual bool	shouldRender() = 0;
    virtual ~IGame() {}
  };
}

#endif /* !IGAME_HH_ */
