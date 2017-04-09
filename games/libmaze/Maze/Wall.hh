//
// Wall.hh for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libmaze/Maze
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Thu Apr  6 00:58:26 2017 Victorien Fischer
// Last update Sun Apr  9 16:29:23 2017 Victorien Fischer
//

#ifndef __WALL_HH__
# define __WALL_HH__

#include "Obstacle.hh"

namespace Arcade
{
  class Wall	: public Obstacle
  {
  public:
    Wall();
    virtual ~Wall();

  public:
    Arcade::Obstacle::Type	getType() const;
    Arcade::Colors		getColor() const;
  };
}

#endif
