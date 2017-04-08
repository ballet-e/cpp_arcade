//
// Wolf3D.hh for cpp_arcade in /home/wurmel_a/rendu/cpp_arcade/games/libwolf3d
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Thu Apr  6 16:33:46 2017 Arnaud WURMEL
// Last update Sat Apr  8 16:47:36 2017 Arnaud WURMEL
//

#ifndef WOLF3D_HH_
# define WOLF3D_HH_

# define SCREEN_WIDTH 100
# define SCREEN_HEIGHT 40
# define MAP_WIDTH 20
# define MAP_HEIGHT 20

# include <iostream>
# include <vector>
# include <memory>
# include "IGame.hh"
# include "Event.hh"
# include "MapLoader.hh"

namespace	Arcade
{
  class	Wolf3D : public Arcade::IGame
  {
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
    void	initGame();
    double	getWallSize();

  private:
    Arcade::IGraphic	*_graphic;
    std::string		_pseudo;
    Arcade::MapLoader	_loader;
    std::vector<std::shared_ptr<Arcade::Map>>	_map;
    Arcade::Position	_player_pos;
  };
}

#endif /* !WOLF3D_HH_ */
