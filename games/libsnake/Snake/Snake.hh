//
// Snake.hh for arcade in /home/wurmel/rendu/cpp_arcade/games/libsnake
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Mon Mar 13 16:06:21 2017 Arnaud WURMEL
// Last update Wed Mar 22 15:14:47 2017 Arnaud WURMEL
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
    void	setUpPseudo(std::string const&);
    LibraryType	getLibraryType() const;
    void	eventListener(Event const&);
    void	render();
    bool	shouldRender();
    Arcade::IGame::GameState	gameState() const;

  public:
    //    unsigned char	**getMap() const;
  private:
    void	showMap();
    void	initMap();
    void	initGame();
    void	drawSquare(unsigned int, unsigned int, unsigned int, unsigned int);
    void	moveSnake();
    void	generateFood();
    bool	eatFood();
    bool	checkSnakeColision() const;
    void	saveScore() const;
    
  private:
    IGraphic	*_graphic_library;
    std::string		_pseudo;
    unsigned int	_score;
    unsigned int	_frame;
    unsigned char	_map[MAP_HEIGHT][MAP_WIDTH];
    Directions		_dir;
    bool		_isInit;
    bool		_hasEat;
    bool		_playing;
    bool		_end;

    bool		_graderMode;

    std::vector<std::pair<unsigned int, unsigned int> >	_body;
    std::vector<std::pair<unsigned int, unsigned int> >	_food;
  };
}

#endif /* !SNAKE_HH_ */
