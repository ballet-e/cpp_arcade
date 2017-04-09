//
// Player.hh for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libsokoban/Sokoban
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Fri Apr  7 00:20:00 2017 Victorien Fischer
// Last update Fri Apr  7 00:27:24 2017 Victorien Fischer
//

#ifndef __PLAYER_HH__
# define __PLAYER_HH__

#include "Obstacle.hh"

namespace Arcade
{
  class	Player : public Obstacle
  {
  public:
    Player();
    ~Player();

  public:
    Arcade::Obstacle::Type	getType() const;
    Arcade::Colors		getColor() const;
  };
}

#endif
