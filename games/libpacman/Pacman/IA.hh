//
// IA.hh for  in /home/ballet_e/CPP/cpp_arcade/games/libpacman/Pacman
// 
// Made by Erwan BALLET
// Login   <ballet_e@epitech.net>
// 
// Started on  Sun Apr  9 13:53:39 2017 Erwan BALLET
// Last update Sun Apr  9 20:17:37 2017 Arnaud WURMEL
//

#ifndef IA_HH_
# define IA_HH_

# include <utility>
# include <memory>
# include <vector>
# include <map>
# include <functional>
# include "MapLoader.hh"

namespace	Arcade
{
  class IA
  {
  public:
    enum Directions
      {
	UP = 0,
	DOWN,
	LEFT,
	RIGHT
      };
    
    enum State
      {
	LIVE = 0,
	DEAD,
	AFRAID
      };
  public:
    IA();
    ~IA();

  public:
    const State&		getState() const;
    void			setState(const State&);
    std::pair<int, int>		getPos() const;
    void			setPos(int, int);
    void			mooveIA(std::vector<std::shared_ptr<Arcade::Map>>, unsigned int, unsigned int);
    Arcade::IA::Directions	invUp();
    Arcade::IA::Directions	invDown();
    Arcade::IA::Directions	invLeft();
    Arcade::IA::Directions	invRight();
    bool			checkUp(std::vector<std::shared_ptr<Arcade::Map>>, unsigned int, unsigned int);
    bool			checkDown(std::vector<std::shared_ptr<Arcade::Map>>, unsigned int, unsigned int);
    bool			checkRight(std::vector<std::shared_ptr<Arcade::Map>>, unsigned int, unsigned int);
    bool			checkLeft(std::vector<std::shared_ptr<Arcade::Map>>, unsigned int, unsigned int);

  private:
    State		_state;
    std::pair<unsigned int, unsigned int>	_pos;
    Directions		_dir;
    std::map<Arcade::IA::Directions,
	     Arcade::IA::Directions (Arcade::IA::*)()>	_changeDir;
    std::map<Arcade::IA::Directions, std::pair<int, int>>	_inc;
    std::map<Arcade::IA::Directions, std::function<bool (std::vector<std::shared_ptr<Arcade::Map>>, unsigned int, unsigned int)>>	_findWay;
  };
}

#endif /* !IA_HH_ */
