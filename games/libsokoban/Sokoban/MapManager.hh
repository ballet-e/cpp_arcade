//
// MapManager.hh for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libsokoban/Sokoban
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Thu Apr  6 20:23:17 2017 Victorien Fischer
// Last update Fri Apr  7 02:34:04 2017 Victorien Fischer
//

#ifndef __MAPMANAGER_HH__
# define __MAPMANAGER_HH__

#include <map>
#include <string>
#include <vector>
#include <utility>
#include "Case.hh"

namespace Arcade
{
  class MapManager
  {
  public:
    MapManager();
    ~MapManager();

  private:
    std::map<char, Arcade::Case *(Arcade::MapManager::*)(int, int)>	_creators;

  private:
    int		_width;
    int		_height;

  public:
    std::vector<Arcade::Case *>	retrieveMap(std::string const &);
    int				getHeight() const;
    int				getWidth() const;
    
  private:
    Arcade::Case		*createBox(int, int);
    Arcade::Case		*createStorage(int, int);
    Arcade::Case		*createStorageBox(int, int);
    Arcade::Case		*createWall(int, int);
    Arcade::Case		*createPlayer(int, int);
    Arcade::Case		*getCase(char, int, int);
    void			setMaxWidth(int);
  };
}

#endif
