//
// Obstacle.hh for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libmaze/Maze
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Thu Apr  6 00:51:48 2017 Victorien Fischer
// Last update Sun Apr  9 16:28:32 2017 Victorien Fischer
//

#ifndef __OBSTACLE_HH__
# define __OBSTACLE_HH__

#include "IGraphic.hh"

namespace Arcade
{
  class Obstacle
  {
  public:
    enum Type
      {
	WALL,
	PLAYER
      };

  public:
    virtual ~Obstacle() {}

  public:
    virtual Arcade::Obstacle::Type	getType() const = 0;
    virtual Arcade::Colors		getColor() const = 0;
  };
}

#endif
