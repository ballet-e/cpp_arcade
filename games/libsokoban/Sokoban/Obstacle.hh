//
// Obstacle.hh for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libsokoban/Sokoban
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Thu Apr  6 00:51:48 2017 Victorien Fischer
// Last update Fri Apr  7 02:10:15 2017 Victorien Fischer
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
	BOX,
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
