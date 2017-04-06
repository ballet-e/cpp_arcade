//
// Sokoban.hh for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libsokoban/Sokoban
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Wed Apr  5 13:19:08 2017 Victorien Fischer
// Last update Thu Apr  6 16:35:05 2017 Victorien Fischer
//

#ifndef __SOKOBAN_HH__
# define __SOKOBAN_HH__

#include <vector>
#include <memory>
#include "Case.hh"
#include "IGame.hh"
#include "Event.hh"

# define MAP_HEIGHT	20
# define MAP_WIDTH	20

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

  private:
    void			saveScore() const;
    void			drawCase(Arcade::Case) const;
    void			showMap() const;

  private:
    IGraphic				*_graphic_library;
    std::string				_pseudo;
    unsigned int			_score;
    std::vector<Arcade::Case>		_map;
    int					_level;

  private:
    bool				_shouldRender;
    bool				_playing;
    bool				_gameover;
    bool				_success;
  };
}
#endif
