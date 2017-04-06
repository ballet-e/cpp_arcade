//
// Enemy.hh for  in /home/ballet_e/CPP/cpp_arcade/games/libsolarfox/SolarFox
// 
// Made by Erwan BALLET
// Login   <ballet_e@epitech.net>
// 
// Started on  Wed Apr  5 07:56:01 2017 Erwan BALLET
// Last update Thu Apr  6 16:53:49 2017 Erwan BALLET
//

#ifndef __ENEMY_HH__
# define __ENEMY_HH__

# include <vector>
# include <utility>
# include "IGame.hh"
# include "Event.hh"
# include "Bullet.hh"

namespace	Arcade
{
  class Enemy
  {
  private:
    std::pair<int, int>	_pos;
    Bullet		_bullet;

  public:
    Enemy();
    ~Enemy();
    
  public:
    std::pair<int, int>	const&	getPos() const;
    void			setPos(int x, int y);
    Bullet const&		getBullet() const;
    void			setBullet(Bullet const& bullet);
    void			setBulletPos(int x, int y);
  };
}

#endif /* !__ENEMY_HH__ */
