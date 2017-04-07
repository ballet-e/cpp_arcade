//
// Arcade.hpp for arcade in /home/wurmel/rendu/cpp_arcade/srcs
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sat Mar 11 23:33:22 2017 Arnaud WURMEL
// Last update Fri Apr  7 22:44:24 2017 Arnaud WURMEL
//

#ifndef ARCADEGAMES_HPP_
# define ARCADEGAMES_HPP_

# include "IGraphic.hh"
# include "IGame.hh"
# include "Errors/Error.hh"

namespace	Arcade
{
  class	ArcadeGames
  {
  public:
    ArcadeGames(Arcade::IGraphic *graphic, Arcade::IGame *game);
    ~ArcadeGames();

  public:
    void	runGame();
    bool	getMissingLibrary();

  private:
    std::string	getFirstLibraryIn(const char *) const;
    bool	getGraphicLibrary(bool use_default = false);
    bool	getGameLibrary();
    Arcade::ILibrary	*loadLibrary(std::string const&) const;

  private:
    std::string	_game_path;
    std::string _lib_path;
    IGraphic	*_graphic;
    IGame	*_game;
  };
}

#endif /* !ARCADE_HPP_ */
