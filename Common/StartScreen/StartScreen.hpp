//
// StartScreen.hpp for arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Thu Mar 16 01:07:18 2017 Arnaud WURMEL
// Last update Mon Apr  3 18:51:13 2017 Arnaud WURMEL
//

#ifndef STARTSCREEN_HPP_
# define STARTSCREEN_HPP_

# include <string>
# include <sys/types.h>
# include <dirent.h>
# include <iostream>
# include "AGraphicElement.hpp"
# include "Button/Button.hh"
# include "TextField/TextField.hpp"
# include "ScoreManager.hpp"

namespace	Arcade
{
  class	StartScreen
  {
  public:
    StartScreen();
    ~StartScreen();

  public:
    void	render(Arcade::IGraphic *);
    std::string const&	getLibraryPath() const;
    std::string const&	getGamePath() const;
    std::string const&	getPseudo() const;

  public:
    void	upKey();
    void	downKey();
    void	enterKey();
    void	enterChar(char);

  private:
    void	loadLibrary();
    void	getScore(Arcade::IGraphic *);

  private:
    void	buttonSelect();
    void	buttonValidate();
    void	buttonCancel();

  private:
    std::vector<Arcade::Selectable *>	_item_list;
    std::vector<Arcade::Button *>	_button_list;
    std::vector<Arcade::TextField *>	_field_list;
    std::vector<Arcade::Selectable *>::iterator	_current_pos;
    std::string				_library_path;
    std::string				_game_path;
    std::string				_pseudo;
  };
}

#endif /* !STARTSCREEN_HPP_ */
