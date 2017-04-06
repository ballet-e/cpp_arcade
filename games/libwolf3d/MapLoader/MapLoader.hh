//
// MapLoader.hh for cpp_arcade in /home/wurmel_a/rendu/cpp_arcade/games/libwolf3d
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Thu Apr  6 18:29:41 2017 Arnaud WURMEL
// Last update Thu Apr  6 19:14:05 2017 Arnaud WURMEL
//

#ifndef MAPLOADER_HH_
# define MAPLOADER_HH_

# include <memory>
# include <vector>

namespace Arcade
{
  enum	CellType
    {
      FREE = 0,
      WALL
    };

  struct	Map
  {
    CellType	type;
  };

  class	MapLoader
  {
  public:
    MapLoader();
    ~MapLoader();

  public:
    std::vector<std::unique_ptr<Map>> const&	getMap();

  private:
    void	loadFile();

  private:
    std::vector<std::unique_ptr<Map>>	_map;
  };
}

#endif /* !MAPLOADER_HH_ */
