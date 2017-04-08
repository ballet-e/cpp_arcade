//
// Wolf3D.hh for cpp_arcade in /home/wurmel_a/rendu/cpp_arcade/games/libwolf3d
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Thu Apr  6 16:33:46 2017 Arnaud WURMEL
// Last update Sat Apr  8 20:33:26 2017 Arnaud WURMEL
//

#ifndef WOLF3D_HH_
# define WOLF3D_HH_

# define SCREEN_WIDTH 95
# define SCREEN_HEIGHT 40
# define MAP_WIDTH 20
# define MAP_HEIGHT 20
# define P 1
# define D 0.5

# include <iostream>
# include <vector>
# include <functional>
# include <utility>
# include <map>
# include <memory>
# include "IGame.hh"
# include "IGraphic.hh"
# include "Event.hh"
# include "MapLoader.hh"

namespace	Arcade
{
  class	Wolf3D : public Arcade::IGame
  {
  public:
    struct	Player
    {
      Position	pos;
      double	angle;
    };
  public:
    Wolf3D();
    ~Wolf3D();

  public:
    void	setUpGraphics(Arcade::IGraphic *);
    void	setUpPseudo(std::string const&);
    LibraryType	getLibraryType() const;
    void	eventListener(Event const&);
    void	render();
    bool	shouldRender();
    Arcade::IGame::GameState	gameState() const;
    unsigned int	getMapWidth() const;
    unsigned int	getMapHeight() const;

  private:
    void	forward();
    void	backward();
    void	rotateLeft();
    void	rotateRight();
    void	drawSquare(unsigned int, unsigned int,
			   Arcade::Position const&,
			   unsigned int);
    
  private:
    void	initGame();
    double	getWallSize(double);

  private:
    Arcade::IGraphic	*_graphic;
    std::string		_pseudo;
    Arcade::MapLoader	_loader;

  private:
    bool		_render;
    unsigned int	_map_width;
    unsigned int	_map_height;
    std::vector<std::shared_ptr<Arcade::Map>>	_map;
    std::map<Arcade::Event::EventType, std::function<void ()>>	_keyBinding;
    Player	_p;
  };
}

#endif /* !WOLF3D_HH_ */
