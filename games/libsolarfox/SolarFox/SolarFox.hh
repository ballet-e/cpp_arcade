//
// SolarFox.hh for arcade in /home/wurmel/rendu/cpp_arcade/games/libsolar_fox
//
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
//
// Started on  Mon Mar 13 16:06:21 2017 Arnaud WURMEL
// Last update Wed Apr  5 16:39:26 2017 Erwan BALLET
//

#ifndef SOLARFOX_HH_
# define SOLARFOX_HH_

# include <vector>
# include <utility>
# include "IGame.hh"
# include "Event.hh"
# include "Bullet.hh"
# include "Enemy.hh"

# define MAP_HEIGHT 20
# define MAP_WIDTH 20

namespace	Arcade
{
  class	IGraphics;

  class	SolarFox : public Arcade::IGame
  {
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
    //initGame();
    
  private:
    Enemy		_Enemy[4];
    Bullet		_Bullet[4];
    IGraphic		*_graphic_library;
    bool		_graderMode;
    bool		_isInit;
    bool		_validatePosition;
    std::string		_pseudo;
    Bullet::Directions	_dir;
  };
}

#endif /* !SOLARFOX_HH_ */
