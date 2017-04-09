//
// Destination.hh for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libmaze/Maze
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Thu Apr  6 00:58:26 2017 Victorien Fischer
// Last update Sun Apr  9 16:26:15 2017 Victorien Fischer
//

#ifndef __STORAGE_HH__
# define __STORAGE_HH__

#include "Floor.hh"

namespace Arcade
{
  class Destination	: public Floor
  {
  public:
    Destination();
    virtual ~Destination();

  public:
    Arcade::Floor::Type		getType() const;
    Arcade::Colors		getColor() const;

  private:
    bool			_box;
  };
}

#endif
