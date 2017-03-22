// Loader.cpp for arcade in /home/wurmel/rendu/cpp_arcade
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Fri Mar 10 20:04:35 2017 Arnaud WURMEL
// Last update Wed Mar 22 10:19:13 2017 Arnaud WURMEL
//

#include <iostream>
#include "ILibrary.hh"
#include "Loader.hh"

/*
** Ctor
** Display a ascii art
*/
Arcade::Loader::Loader()
{
  _handler = NULL;
  _library = NULL;
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
  unsigned int	(*getMagic)();
  ILibrary	*(*getLibrary)();

  _handler = dlopen(path.c_str(), RTLD_LAZY);
  if (_handler)
    {
      if ((getMagic = reinterpret_cast<unsigned int (*)()>(dlsym(_handler, "getMagic"))) == NULL)
	return false;
      if ((*getMagic)() == MAGIC_NUMBER)
	{
	  if ((getLibrary = reinterpret_cast<ILibrary * (*)()>(dlsym(_handler, "getLibrary"))) == NULL)
	    return false;
	  if ((_library = (*getLibrary)()) == NULL)
	    {
	      return false;
	    }
	  return true;
	}
      return false;
    }
  return false;
}

Arcade::ILibrary	*Arcade::Loader::getLibrary() const
{
  if (_library)
    return _library;
  return NULL;
}

/*
** Dtor
*/
Arcade::Loader::~Loader() {}
