//
// Text.hh for  in /home/wurmel_a/rendu/cpp_arcade/lib/libncurses
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Tue Apr  4 23:09:07 2017 Arnaud WURMEL
// Last update Wed Apr  5 11:20:22 2017 Arnaud WURMEL
//

#ifndef TEXT_HH_
# define TEXT_HH_

# include <iostream>
# include "IGraphic.hh"

namespace	Arcade
{
  class	Text
  {
  public:
    Text(std::string const&, int, int, Arcade::Colors const&, Arcade::Colors const&);
    ~Text();

  public:
    std::string const&	getText() const;
    Arcade::Colors const&	getFont() const;
    Arcade::Colors const&	getBack() const;
    int	getX() const;
    int	getY() const;

  private:
    std::string	_print;
    int		_x;
    int		_y;
    Arcade::Colors	_font;
    Arcade::Colors	_back;
  };
}

#endif /* !TEXT_HH_ */
