//
// SFMLWrapper.hh for cpp_arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sat Mar 11 22:34:07 2017 Arnaud WURMEL
// Last update Sat Mar 11 23:21:04 2017 Arnaud WURMEL
//

#ifndef SFMLWRAPPER_HH_
# define SFMLWRAPPER_HH_

# include <SFML/Window.hpp>
# include "IGraphic.hh"

namespace Arcade
{
  class	SFMLWrapper : public Arcade::IGraphic
  {
  public:
    SFMLWrapper();
    ~SFMLWrapper();
  public:
    bool	renderWindowStart();
    bool	createWindow(unsigned int, unsigned int);
    bool	drawSquare64x64(unsigned int, unsigned int, unsigned int);
    LibraryType	getLibraryType() const;

  private:
    sf::Window	*_window;
  };
}

#endif /* !SMFLWRAPPER_HH_ */
