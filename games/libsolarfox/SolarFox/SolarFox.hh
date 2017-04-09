//
// SolarFox.hh for arcade in /home/wurmel/rendu/cpp_arcade/games/libsolar_fox
//
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
//
// Started on  Mon Mar 13 16:06:21 2017 Arnaud WURMEL
// Last update Sun Apr  9 12:20:58 2017 Erwan BALLET
//

#ifndef SOLARFOX_HH_
# define SOLARFOX_HH_

# include <vector>
# include <utility>
# include <map>
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
    unsigned int		getMapWidth() const;
    unsigned int		getMapHeight() const;
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
    void	initMap();
    void	showMap();
    void	drawSquare(unsigned int size, unsigned int color,
			   unsigned int pos_x, unsigned int pos_y);
    void	mooveEnemy(Enemy En, int i);
    void	enemyShoot(int i);
    void	mooveShip();
    int		bulletEnd(Arcade::Bullet bullet);
    void	amIDead();
    void	setPoints();
    void	didIGetPoints();
    void	saveScore() const;
    void	mooveMyShoot();
    std::pair<int, int>	incUp(std::pair<int, int>);
    std::pair<int, int>	incDown(std::pair<int, int>);
    std::pair<int, int>	incLeft(std::pair<int, int>);
    std::pair<int, int>	incRight(std::pair<int, int>);
    
  private:
    std::map<Arcade::Bullet::Directions, std::pair<int, int> (Arcade::SolarFox::*)(std::pair<int, int>)>	_incDir;
    Enemy		_Enemy[4];
    IGraphic		*_graphic_library;
    bool		_graderMode;
    bool		_isInit;
    bool		_validatePosition;
    bool		_end;
    unsigned int	_frame;
    bool		_scoreSet;
    std::string		_pseudo;
    Bullet::Directions	_dir;
    std::vector<std::vector<unsigned char>>	_map;;
    std::pair<int, int>	_ship;
    Bullet		_myShoot;
    unsigned char	_travel;
    int			_score;
    int			_lv;
    int			_enemyMoove;
    bool		_points;
    int			_shouldMoove;
    std::vector<std::pair<int, int>>		_pointTab;
  };
}

#endif /* !SOLARFOX_HH_ */
