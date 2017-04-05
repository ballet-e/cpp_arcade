//
// Bullet.hh for  in /home/ballet_e/CPP/cpp_arcade/games/libsolarfox/SolarFox
// 
// Made by Erwan BALLET
// Login   <ballet_e@epitech.net>
// 
// Started on  Wed Apr  5 08:04:00 2017 Erwan BALLET
// Last update Thu Apr  6 00:01:26 2017 Erwan BALLET
//

#ifndef __BULLET_HH__
# define __BULLET_HH__

# include <vector>
# include <utility>
# include "IGame.hh"
# include "Event.hh"

namespace	Arcade
{
  class Bullet
  {
  public:
    enum        Directions
      {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	STOP
      };
  private:
    std::pair<int, int>	_pos;
    Directions		_dir;

  public:
    Bullet();
    ~Bullet();
    
  public:
    std::pair<int, int>	const& getPos() const;
    void	setPos(int x, int y);
    Directions	const& getDir() const;
    void        setDir(Directions const& dir);
  };
}

#endif /* !__BULLET_HH__ */
