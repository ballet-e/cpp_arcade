//
// Sokoban.hh for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libsokoban/Sokoban
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Wed Apr  5 13:19:08 2017 Victorien Fischer
// Last update Wed Apr  5 13:24:25 2017 Victorien Fischer
//

#ifndef __SOKOBAN_HH__
# define __SOKOBAN_HH__

#include <map>
#include <utility>
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
    Arcade::IGame::GameState	gameState() const;

  private:
    IGraphic				*_graphic_library;
    std::string				_pseudo;
    unsigned int			_score;
    std::map<std::pair<int, int>, char>	_map;
  };
}
#endif
