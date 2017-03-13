//
// SFMLWrapper.hh for cpp_arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sat Mar 11 22:34:07 2017 Arnaud WURMEL
// Last update Mon Mar 13 17:32:27 2017 Arnaud WURMEL
//

#ifndef SFMLWRAPPER_HH_
# define SFMLWRAPPER_HH_

# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include <vector>
# include "Button.hh"
# include "IGraphic.hh"
# include "IGame.hh"

namespace Arcade
{
  class	SFMLWrapper : public Arcade::IGraphic
  {
  public:
    SFMLWrapper();
    ~SFMLWrapper();
  public:
    bool	renderWindowStart();
    void	renderWindowGame(unsigned int, unsigned int, IGame*);
    bool	setPixel(unsigned int, unsigned int, unsigned int);
    LibraryType	getLibraryType() const;
    void	setText(std::string const&, unsigned int, TextMode const&);

  private:
    bool	createWindow(unsigned int, unsigned int);

  public:
    std::string const&	getLibraryPath() const;
    std::string const&	getGamePath() const;

  private:
    void	drawTitle();
    void	getAllLibrary();
    void	drawWindow();
    bool	keyboardHandler(sf::Event const&);

  private:
    sf::RenderWindow		*_window;
    std::vector<Button *>	_button_list;
    std::vector<Button *>::iterator	_current_pos;

    std::string		_library_path;
    std::string		_game_path;
  };
}

#endif /* !SMFLWRAPPER_HH_ */
