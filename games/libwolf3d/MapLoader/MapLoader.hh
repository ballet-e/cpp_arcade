//
// MapLoader.hh for cpp_arcade in /home/wurmel_a/rendu/cpp_arcade/games/libwolf3d
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Thu Apr  6 18:29:41 2017 Arnaud WURMEL
// Last update Thu Apr  6 21:29:50 2017 Arnaud WURMEL
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
    Map(CellType type) : _type(type)
    {}

    CellType	_type;
  };

  class	MapLoader
  {
  public:
    MapLoader();
    ~MapLoader();

  public:
    std::vector<std::vector<std::shared_ptr<Map>>> const&	getMap();
    void	deleteMap();

  private:
    void	loadFile();

  };
}

#endif /* !MAPLOADER_HH_ */
