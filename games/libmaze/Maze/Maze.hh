//
// Maze.hh for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libmaze/Maze
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Wed Apr  5 13:19:08 2017 Victorien Fischer
// Last update Sun Apr  9 16:36:33 2017 Victorien Fischer
//

#ifndef __MAZE_HH__
# define __MAZE_HH__

#include <vector>
#include <memory>
#include "Case.hh"
#include "Wall.hh"
#include "IGame.hh"
#include "Event.hh"
#include "Player.hh"
#include "Destination.hh"
#include "MapManager.hh"

namespace Arcade
{
  class Maze : public Arcade::IGame
  {
  public:
    Maze();
    ~Maze();

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

  private:
    IGraphic				*_graphic_library;
    std::string				_pseudo;
    std::vector<Arcade::Case *>		_map;
    Arcade::MapManager			_mapManager;
    unsigned int			_move;
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
