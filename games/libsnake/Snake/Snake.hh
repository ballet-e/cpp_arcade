//
// Snake.hh for arcade in /home/wurmel/rendu/cpp_arcade/games/libsnake
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Mon Mar 13 16:06:21 2017 Arnaud WURMEL
// Last update Mon Mar 13 18:11:09 2017 Arnaud WURMEL
//

#ifndef SNAKE_HH_
# define SNAKE_HH_

# include "IGame.hh"
# include "Event.hh"

class	IGraphics;

namespace	Arcade
{
  class	Snake : public Arcade::IGame
  {
  public:
    Snake();
    ~Snake();

  public:
    void	setUpGraphics(IGraphic *);
    LibraryType	getLibraryType() const;
    void	eventListener(Event const&);
    void	render();

  private:
    IGraphic	*_graphic_library;
  };
}

#endif /* !SNAKE_HH_ */
