//
// Sokoban.hh for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libsokoban/Sokoban
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Wed Apr  5 13:19:08 2017 Victorien Fischer
// Last update Fri Apr  7 23:19:28 2017 Arnaud WURMEL
//

#ifndef __SOKOBAN_HH__
# define __SOKOBAN_HH__

#include <vector>
#include <memory>
#include "Box.hh"
#include "Case.hh"
#include "Wall.hh"
#include "IGame.hh"
#include "Event.hh"
#include "Player.hh"
#include "Storage.hh"
#include "MapManager.hh"

namespace Arcade
{
  class Sokoban : public Arcade::IGame
  {
  public:
    Sokoban();
    ~Sokoban();

  public:
    void			setUpGraphics(Arcade::IGraphic *);
    void			setUpPseudo(std::string const &);
    LibraryType			getLibraryType() const;
    void			eventListener(Event const &);
    void			render();
    bool			shouldRender();
    Arcade::IGame::GameState	gameState() const;
    unsigned int		getMapWidth() const;
    unsigned int		getMapHeight() const;
    void			initGame();

  private:
    void			saveScore() const;
    void			drawCase(Arcade::Case *) const;
    void			showMap() const;

  private:
    void			checkMap();
    void			checkEnd();
    Arcade::Case		*getPlayerCase();
    Arcade::Case		*getPositionCase(int, int);
    bool			canPush(Arcade::Case *, Arcade::Event const &);

  private:
    IGraphic				*_graphic_library;
    std::string				_pseudo;
    std::vector<Arcade::Case *>		_map;
    Arcade::MapManager			_mapManager;
    unsigned int			_push;
    std::string				_errorMsg;
    int					_width;
    int					_height;

  private:
    bool				_shouldRender;
    bool				_playing;
    bool				_gameover;
    bool				_success;
    bool				_error;
  };
}
#endif
