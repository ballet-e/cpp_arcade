//
// Loader.cpp for arcade in /home/wurmel/rendu/cpp_arcade
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Fri Mar 10 20:04:35 2017 Arnaud WURMEL
// Last update Fri Mar 10 20:47:38 2017 Arnaud WURMEL
//

#include <iostream>
#include "Loader.hh"

/*
** Ctor
** Display a ascii art
*/
Arcade::Loader::Loader()
{
  std::cout << "    ___                        __   " << std::endl;
  std::cout << "   /   |  ______________ _____/ /__ " << std::endl;
  std::cout << "  / /| | / ___/ ___/ __ `/ __  / _ \\" << std::endl;
  std::cout << " / ___ |/ /  / /__/ /_/ / /_/ /  __/" << std::endl;
  std::cout << "/_/  |_/_/   \\___/\\__,_/\\__,_/\\___/ " << std::endl;
  std::cout << "\033[0m" << std::endl << std::endl;
}

/*
** Utilities to display good formatted message and indication to user
*/
void	Arcade::Loader::displayMessage(std::string const& message, Arcade::Loader::MessageType const& type)
{
  std::cout << "Arcade : " << message;
  if (type == Arcade::Loader::ERROR)
    std::cout << "\t\033[31mKO\033[0m";
  else if (type == Arcade::Loader::SUCCESS)
    std::cout << "\t\033[32mOK\033[0m";
  std::cout << std::endl;
}

/*
** Function in order to load librarie, it would do a second operation,
** He will call a function of librarie call 'getMagic()'
** And check this magic, in case of wrong magic, throw exception
** Else keep handler (dlopen) into this class
*/
bool	Arcade::Loader::loadLib(std::string const& path)
{
  static_cast<void>(path);
  return (false);
}

/*
** Dtor
*/
Arcade::Loader::~Loader() {}
