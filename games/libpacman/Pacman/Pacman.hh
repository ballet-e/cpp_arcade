//
// Pacman.hh for  in /home/ballet_e/CPP/cpp_arcade/games/libpacman/Pacman
// 
// Made by Erwan BALLET
// Login   <ballet_e@epitech.net>
// 
// Started on  Sun Apr  9 13:29:12 2017 Erwan BALLET
// Last update Sun Apr  9 18:43:36 2017 Arnaud WURMEL
//

#ifndef PACMAN_HH_
# define PACMAN_HH_

# include <utility>
# include <functional>
# include "IGame.hh"
# include "IGraphic.hh"
# include "Event.hh"
# include "MapLoader.hh"

namespace	Arcade
{
  class IGraphics;

  class Pacman : public Arcade::IGame
  {
  public:
    enum	Direction
      {
	None,
	Up,
	Down,
	Left,
	Right
      };
  public:
    Pacman();
    ~Pacman();

  public:
    void	setUpGraphics(Arcade::IGraphic *);
    void	setUpPseudo(std::string const&);
    LibraryType	getLibraryType() const;
    void	eventListener(Event const&);
    void	drawSquare(unsigned int, unsigned int, unsigned int, Arcade::Colors const&);
    void	render();
    bool	shouldRender();
    void	initGame();
    unsigned int	getMapWidth() const;
    unsigned int	getMapHeight() const;
    Arcade::IGame::GameState	gameState() const;

  private:
    void	moveP();
    void	eat();

  public:
    // void	whereAmI();
    // void	getMap();
    void	goUp();
    void	goDown();
    void	goLeft();
    void	goRight();
    // void	goForward();
    // void	makeShoot();
    // void	illegal();
    // void	playRound();

  private:
    bool	canLeft() const;
    bool	canRight() const;
    bool	canUp() const;
    bool	canDown() const;

  private:
    std::string	_pseudo;
    IGraphic	*_graphic_library;
    bool	_graderMode;
    bool	_end;
    unsigned int	_frame;

  private:
    Arcade::MapLoader	_loader;
    std::vector<std::shared_ptr<Map>>	_map;
    Direction	_dir;
    Direction	_validate;
    unsigned int	_width;
    unsigned int	_height;
    unsigned int	_score;
    Position	_p;
  };
}

#endif /* !PACMAN_HH_ */
