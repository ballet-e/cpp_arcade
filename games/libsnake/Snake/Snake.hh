//
// Snake.hh for arcade in /home/wurmel/rendu/cpp_arcade/games/libsnake
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Mon Mar 13 16:06:21 2017 Arnaud WURMEL
// Last update Tue Mar 14 19:04:56 2017 Arnaud WURMEL
//

#ifndef SNAKE_HH_
# define SNAKE_HH_

# include <vector>
# include <utility>
# include "IGame.hh"
# include "Event.hh"

# define MAP_HEIGHT 20
# define MAP_WIDTH 20

namespace	Arcade
{
  class	IGraphics;

  class	Snake : public Arcade::IGame
  {
  public:
    enum	Directions
      {
	LEFT,
	RIGHT,
	UP,
	DOWN
      };
  public:
    Snake();
    ~Snake();

  public:
    void	setUpGraphics(Arcade::IGraphic *);
    LibraryType	getLibraryType() const;
    void	eventListener(Event const&);
    void	render();
    bool	shouldRender();
    Arcade::IGame::GameState	gameState() const;

  private:
    void	showMap();
    void	initMap();
    void	initGame();
    void	drawSquare(unsigned int, unsigned int, unsigned int, unsigned int);
    void	moveSnake();
    void	generateFood();
    bool	eatFood();
    bool	checkSnakeColision() const;
    
  private:
    IGraphic	*_graphic_library;
    unsigned int	_score;
    unsigned int	_frame;
    unsigned char	_map[MAP_HEIGHT][MAP_WIDTH];
    Directions		_dir;
    bool		_isInit;
    bool		_hasEat;
    bool		_playing;
    bool		_end;

    std::vector<std::pair<unsigned int, unsigned int> >	_body;
    std::vector<std::pair<unsigned int, unsigned int> >	_food;
  };
}

#endif /* !SNAKE_HH_ */
