//
// Arcade.hpp for arcade in /home/wurmel/rendu/cpp_arcade/srcs
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sat Mar 11 23:33:22 2017 Arnaud WURMEL
// Last update Sat Apr  8 01:09:14 2017 Arnaud WURMEL
//

#ifndef ARCADEGAMES_HPP_
# define ARCADEGAMES_HPP_

# include <vector>
# include <map>
# include <functional>
# include <utility>
# include "IGraphic.hh"
# include "IGame.hh"
# include "Errors/Error.hh"

namespace	Arcade
{
  class	ArcadeGames
  {
  public:
    ArcadeGames(Arcade::IGraphic *graphic, Arcade::IGame *game, std::string const&);
    ~ArcadeGames();

  public:
    void	runGame();
    bool	getMissingLibrary();

  private:
    bool	setUpGames(std::string const&);
    std::vector<std::string>	getLibraryForDirectory(std::string const&) const;
    std::string	getFirstLibraryIn(const char *) const;
    bool	getGraphicLibrary(bool use_default = false, std::string path = "");
    bool	getGameLibrary();
    Arcade::ILibrary	*loadLibrary(std::string const&) const;
    bool	handleExitStatus(Arcade::ExitStatus const&);

  private:
    bool	loadNextLib();
    bool	loadPrevLib();
    bool	loadNextGame();
    bool	loadPrevGame();
    bool	backToMenu();

  private:
    std::string	_game_path;
    std::string _lib_path;
    std::string	_pseudo;
    IGraphic	*_graphic;
    IGame	*_game;
    std::map<Arcade::ExitStatus, std::function<bool ()>>	_callback;
  };
}

#endif /* !ARCADE_HPP_ */
