//
// Loader.hh for Arcade in /home/wurmel/rendu/cpp_arcade
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Fri Mar 10 20:02:16 2017 Arnaud WURMEL
// Last update Mon Mar 13 15:48:21 2017 Arnaud WURMEL
//

#ifndef LOADER_HH_
# define LOADER_HH_

# include <string>
# include <dlfcn.h>
# include "IGraphic.hh"

namespace Arcade
{
  class	Loader
  {

  public:
    enum MessageType
    {
      ERROR,
      SUCCESS,
      UNDEFINED
    };
 
  public:
    Loader();
    ~Loader();

  public:
    bool	loadLib(std::string const&);

  public:
    void	displayMessage(std::string const&, Arcade::Loader::MessageType const&);

  public:
    ILibrary	*getLibrary() const;

  private:
    void	*_handler;
    ILibrary	*_library;
  };
}

#endif /* !LOADER_HH_ */
