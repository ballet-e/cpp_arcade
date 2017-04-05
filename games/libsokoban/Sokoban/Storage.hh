//
// Storage.hh for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libsokoban/Sokoban
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Thu Apr  6 00:58:26 2017 Victorien Fischer
// Last update Thu Apr  6 01:02:50 2017 Victorien Fischer
//

#ifndef __STORAGE_HH__
# define __STORAGE_HH__

#include "Obstacle.hh"

namespace Arcade
{
  class Storage	: public Obstacle
  {
  public:
    Storage();
    virtual ~Storage();

  public:
    Arcade::Obstacle::Type	getType() const;
  };
}

#endif
