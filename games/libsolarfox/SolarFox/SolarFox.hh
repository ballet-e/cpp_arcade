//
// SolarFox.hh for arcade in /home/wurmel/rendu/cpp_arcade/games/libsolar_fox
//
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
//
// Started on  Mon Mar 13 16:06:21 2017 Arnaud WURMEL
// Last update Tue Apr  4 11:20:40 2017 Ballet Erwan
//

#ifndef SOLARFOX_HH_
# define SOLARFOX_HH_

# include <vector>
# include <utility>
# include "IGame.hh"
# include "Event.hh"

# define MAP_HEIGHT 20
# define MAP_WIDTH 20

namespace	Arcade
{
  class	IGraphics;

  class	SolarFox : public Arcade::IGame
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
    SolarFox();
    ~SolarFox();

  public:
    void	setUpGraphics(Arcade::IGraphic *);
    void	setUpPseudo(std::string const&);
    LibraryType	getLibraryType() const;
    void	eventListener(Event const&);
    void	render();
    bool	shouldRender();
    Arcade::IGame::GameState	gameState() const;

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
    std::string		_pseudo;
  };
}

#endif /* !SOLARFOX_HH_ */
