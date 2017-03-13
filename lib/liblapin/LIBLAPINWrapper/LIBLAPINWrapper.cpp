//
// LIBLAPINWrapper.cpp for arcade in /home/ballet/CPP/cpp_arcade/lib/liblapin/LIBLAPINWrapper/
//
// Made by Ballet Erwan
// Login   <erwan.ballet@epitech.eu>
//
// Started on  Mon Mar 13 10:41:10 2017 Ballet Erwan
// Last update Mon Mar 13 18:11:52 2017 Ballet Erwan
//

#include "IGraphic.hh"
#include "lapin.h"
#include "LIBLAPINWrapper.hh"

Arcade::LIBLAPINWrapper::LIBLAPINWrapper() {
  this->win = 0;
}

bool    Arcade::LIBLAPINWrapper::renderWindowStart() {
  this->win = bunny_start(800, 600, false, "Arcade");
  if (this->win == NULL)
    {
      bunny_printlerr("Cannot open the window.");
      return (false);
    }
  bunny_clear(&(this->win)->buffer, PINK2);
  bunny_display(this->win);
  bunny_loop(this->win, 25, NULL);
  bunny_stop(this->win);
  return (true);
}

void	Arcade::LIBLAPINWrapper::renderWindowGame(unsigned int x, unsigned int y, IGame* game) {
  static_cast<void>(x);
  static_cast<void>(y);
  static_cast<void>(game);
}

bool	Arcade::LIBLAPINWrapper::setPixel(unsigned int x, unsigned int y, unsigned int color) {
  static_cast<void>(x);
  static_cast<void>(y);
  static_cast<void>(color);
  return (true);
}

void	Arcade::LIBLAPINWrapper::setText(std::string const& text, unsigned int y, TextMode const& mode) {
  static_cast<void>(text);
  static_cast<void>(y);
  static_cast<void>(mode);
}

Arcade::LIBLAPINWrapper::~LIBLAPINWrapper() {};
