//
// Loader.hh for Arcade in /home/wurmel/rendu/cpp_arcade
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Fri Mar 10 20:02:16 2017 Arnaud WURMEL
// Last update Fri Mar 10 20:47:53 2017 Arnaud WURMEL
//

#ifndef LOADER_HH_
# define LOADER_HH_

# include <string>
# include <dlfcn.h>

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
  };
}

#endif /* !LOADER_HH_ */
