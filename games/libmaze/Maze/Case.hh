//
// Case.hh for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libmaze/Maze
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Thu Apr  6 13:20:54 2017 Victorien Fischer
// Last update Sun Apr  9 16:25:13 2017 Victorien Fischer
//

#ifndef __CASE_HH__
# define __CASE_HH__

#include "Floor.hh"
#include "Obstacle.hh"

namespace Arcade
{
  class	Case
  {
  public:
    Case(int x = 0, int y = 0, Arcade::Obstacle *obs = NULL, Arcade::Floor *flr = NULL);
    Case(Case const &);
    ~Case();

  public:
    int				getX() const;
    int				getY() const;
    Arcade::Colors		getColor() const;
    Arcade::Obstacle		*getObstacle() const;
    Arcade::Floor		*getFloor() const;
    void			setObstacle(Arcade::Obstacle *);
    void			setFloor(Arcade::Floor *);
    
  private:
    int			_x;
    int			_y;
    Arcade::Obstacle	*_obs;
    Arcade::Floor	*_flr;
  };
}

#endif
