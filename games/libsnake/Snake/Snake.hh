//
// Snake.hh for arcade in /home/wurmel/rendu/cpp_arcade/games/libsnake
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Mon Mar 13 16:06:21 2017 Arnaud WURMEL
// Last update Mon Mar 13 16:31:35 2017 Arnaud WURMEL
//

#ifndef SNAKE_HH_
# define SNAKE_HH_

//# include "IGraphic.hh"
# include "IGame.hh"

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

  private:
    IGraphic	*_graphic_library;
  };
}

#endif /* !SNAKE_HH_ */
