//
// Snake.hh for arcade in /home/wurmel/rendu/cpp_arcade/games/libsnake
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Mon Mar 13 16:06:21 2017 Arnaud WURMEL
// Last update Fri Apr  7 23:00:03 2017 Arnaud WURMEL
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
    unsigned int	getMapWidth() const;
    unsigned int	getMapHeight() const;
    void	initGame();

    /*
    ** Koalinette protocol
    */
  public:
    void	whereAmI();
    void	getMap();
    void	goUp();
    void	goDown();
    void	goLeft();
    void	goRight();
    void	goForward();
    void	makeShoot();
    void	illegal();
    void	playRound();

  private:
    void	showMap();
    void	initMap();
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
    std::vector<std::vector<unsigned char> >	_map;
    Directions		_dir;
    bool		_isInit;
    bool		_hasEat;
    bool		_playing;
    bool		_end;

    bool		_graderMode;
    bool		_validatePosition;

    std::vector<std::pair<unsigned int, unsigned int> >	_body;
    std::vector<std::pair<unsigned int, unsigned int> >	_food;
  };
}

#endif /* !SNAKE_HH_ */
