//
// LIBLAPINWrapper.cpp for arcade in /home/ballet/CPP/cpp_arcade/lib/liblapin/LIBLAPINWrapper/
//
// Made by Ballet Erwan
// Login   <erwan.ballet@epitech.eu>
//
// Started on  Mon Mar 13 10:41:10 2017 Ballet Erwan
// Last update Mon Apr  3 13:21:41 2017 Ballet Erwan
//

#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <exception>
#include "IGraphic.hh"
#include "lapin.h"
#include "LIBLAPINWrapper.hh"

Arcade::LIBLAPINWrapper::LIBLAPINWrapper() {
  this->_win = NULL;
}

Arcade::LibraryType	Arcade::LIBLAPINWrapper::getLibraryType() const {
  return (Arcade::GRAPHIC);
}

bool    Arcade::LIBLAPINWrapper::renderWindowStart() {
  this->_win = bunny_start(1280, 1060, false, "Arcade");
  if (this->_win == NULL)
    {
      bunny_printlerr("Cannot open the window.");
      return (false);
    }
  bunny_clear(&(this->_win)->buffer, PINK2);
  bunny_display(this->_win);
  // bunny_loop(this->win, 60, NULL);
  bunny_stop(this->_win);
  return (true);
}

void	Arcade::LIBLAPINWrapper::renderWindowGame(unsigned int width, unsigned int height, IGame* game) {
  static_cast<void>(width);
  static_cast<void>(height);
  static_cast<void>(game);
}

bool	Arcade::LIBLAPINWrapper::setPixel(unsigned int x, unsigned int y, unsigned int color) {
  static_cast<void>(x);
  static_cast<void>(y);
  static_cast<void>(color);
  return (true);
}

void	Arcade::LIBLAPINWrapper::setText(std::string const& to_print,
              unsigned int y,
              Arcade::ElementPosition const& mode,
              unsigned int fontSize,
              Arcade::Colors const& fontColor,
              Arcade::Colors const& backgroundColor)
{
  static_cast<void>(to_print);
  static_cast<void>(y);
  static_cast<void>(mode);
  static_cast<void>(fontSize);
  static_cast<void>(fontColor);
  static_cast<void>(backgroundColor);
}

unsigned int	Arcade::LIBLAPINWrapper::getDrawableHeight() const {
  return (0);
}
unsigned int	Arcade::LIBLAPINWrapper::getDrawableWidth() const {
  return (0);
}

std::string const&	Arcade::LIBLAPINWrapper::getGamePath() const {
  return _screen.getLibraryPath();
}

std::string const&	Arcade::LIBLAPINWrapper::getLibraryPath() const {
  return _screen.getGamePath();
}

Arcade::LIBLAPINWrapper::~LIBLAPINWrapper() {};
