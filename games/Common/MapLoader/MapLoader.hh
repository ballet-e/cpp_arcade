//
// MapLoader.hh for cpp_arcade in /home/wurmel_a/rendu/cpp_arcade/games/libwolf3d
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Thu Apr  6 18:29:41 2017 Arnaud WURMEL
// Last update Sun Apr  9 16:02:58 2017 Arnaud WURMEL
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
      WALL,
      EAT,
      POWER_UP,
      PLAYER
    };

    struct	Position
    {
      double	x;
      double	y;
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
    std::vector<std::shared_ptr<Map>> const&	getMap(std::string const&);
    Position const&	getPlayerPosition() const;
    void	deleteMap();

  public:
    unsigned int	getMapHeight() const;
    unsigned int	getMapWidth() const;

  private:
    void	loadFile(std::string const&);
    bool	foundPosition();

  private:
    std::vector<std::shared_ptr<Map>>	_map;
    Arcade::Position	_p;
    unsigned int	_width;
    unsigned int	_height;
  };
}

#endif /* !MAPLOADER_HH_ */
