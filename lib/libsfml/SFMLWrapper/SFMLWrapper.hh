//
// SFMLWrapper.hh for cpp_arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sat Mar 11 22:34:07 2017 Arnaud WURMEL
// Last update Thu Mar 16 02:51:42 2017 Arnaud WURMEL
//

#ifndef SFMLWRAPPER_HH_
# define SFMLWRAPPER_HH_

# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include <vector>
# include "Button.hh"
# include "IGraphic.hh"
# include "IGame.hh"
# include "ScoreManager.hpp"
# include "StartScreen.hpp"

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
    void	setText(std::string const&to_print, unsigned int y,
			Arcade::ElementPosition const& mode,
			unsigned int fontSize = 15,
			Arcade::Colors const& fontColor = Arcade::Colors::WHITE,
			Arcade::Colors const& backgroundColor = Arcade::Colors::BLACK);
    unsigned int	getDrawableHeight() const;
    unsigned int	getDrawableWidth() const;

  private:
    bool	createWindow(unsigned int, unsigned int);

  public:
    std::string const&	getLibraryPath() const;
    std::string const&	getGamePath() const;

  private:
    void	renderGame();
    void	drawTitle();
    void	drawWindow();
    bool	keyboardHandler(sf::Event const&);
    void	getColor(sf::Color[8]) const;

  private:
    sf::RenderWindow		*_window;
    sf::Image			_image;
    Arcade::StartScreen		_screen; 
  };
}

#endif /* !SMFLWRAPPER_HH_ */
