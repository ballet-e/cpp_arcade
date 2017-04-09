//
// Pacman.hh for  in /home/ballet_e/CPP/cpp_arcade/games/libpacman/Pacman
// 
// Made by Erwan BALLET
// Login   <ballet_e@epitech.net>
// 
// Started on  Sun Apr  9 13:29:12 2017 Erwan BALLET
// Last update Sun Apr  9 13:47:48 2017 Erwan BALLET
//

#ifndef PACMAN_HH_
# define PACMAN_HH_

# include <utility>
# include "IGame.hh"
# include "Event.hh"

namespace	Arcade
{
  class IGraphics;

  class Pacman : public Arcade::IGame
  {
  public:
    Pacman();
    ~Pacman();

  public:
    void	setUpGraphics(Arcade::IGraphic *);
    void	setUpPseudo(std::string const&);
    LibraryType	getLibraryType() const;
    void	eventListener(Event const&);
    void	render();
    bool	shouldRender();
    void	initGame();
    unsigned int	getMapWidth() const;
    unsigned int	getMapHeight() const;
    Arcade::IGame::GameState	gameState() const;

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
    IGraphic	*_graphic_library;
  };
}

#endif /* !PACMAN_HH_ */
