//
// Box.hh for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libsokoban/Sokoban
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Thu Apr  6 00:58:26 2017 Victorien Fischer
// Last update Thu Apr  6 15:00:43 2017 Victorien Fischer
//

#ifndef __BOX_HH__
# define __BOX_HH__

#include "Obstacle.hh"

namespace Arcade
{
  class Box	: public Obstacle
  {
  public:
    Box();
    virtual ~Box();

  public:
    Arcade::Obstacle::Type	getType() const;
    Arcade::Colors		getColor() const;
  };
}

#endif
