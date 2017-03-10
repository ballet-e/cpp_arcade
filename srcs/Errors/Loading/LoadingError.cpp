//
// LoadingError.cpp for Arcade in /home/wurmel/rendu/cpp_arcade/srcs/Errors
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Fri Mar 10 20:35:53 2017 Arnaud WURMEL
// Last update Fri Mar 10 20:39:35 2017 Arnaud WURMEL
//

#include "LoadingError.hh"

Arcade::LoadingError::LoadingError(std::string const& what)
{
  _what = what;
}

Arcade::LoadingError::LoadingError(const char *what)
{
  _what = std::string(what);
}

char const*	Arcade::LoadingError::what() const throw()
{
  return (_what.c_str());
}

Arcade::LoadingError::~LoadingError() {}
