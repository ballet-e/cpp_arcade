//
// Floor.hh for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libsokoban/Sokoban
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Fri Apr  7 02:07:54 2017 Victorien Fischer
// Last update Fri Apr  7 02:11:23 2017 Victorien Fischer
//

#ifndef __FLOOR_HH__
# define __FLOOR_HH__

#include "IGraphic.hh"

namespace Arcade
{
  class Floor
  {
  public:
    enum Type
      {
	NORMAL,
	STORAGE
      };

  public:
    virtual ~Floor() {}

  public:
    virtual Arcade::Floor::Type		getType() const = 0;
    virtual Arcade::Colors		getColor() const = 0;
  };
}

#endif
