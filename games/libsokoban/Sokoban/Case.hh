//
// Case.hh for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libsokoban/Sokoban
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Thu Apr  6 13:20:54 2017 Victorien Fischer
// Last update Thu Apr  6 15:05:18 2017 Victorien Fischer
//

#ifndef __CASE_HH__
# define __CASE_HH__

#include "Obstacle.hh"

namespace Arcade
{
  class	Case
  {
  public:
    Case(int, int, Arcade::Obstacle *);
    Case(Case const &);
    ~Case();

  public:
    int				getX() const;
    int				getY() const;
    Arcade::Colors		getColor() const;
    Arcade::Obstacle		*getObstacle() const;
    void			setObstacle(Arcade::Obstacle *);
    
  private:
    int			_x;
    int			_y;
    Arcade::Obstacle	*_obs;
  };
}

#endif
