//
// ILibrary.hh for Arcade in /home/wurmel/rendu/cpp_arcade
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Sat Mar 11 23:29:29 2017 Arnaud WURMEL
// Last update Sat Mar 11 23:31:28 2017 Arnaud WURMEL
//

#ifndef ILIBRARY_HH_
# define ILIBRARY_HH_

namespace	Arcade
{
  enum	LibraryType
    {
      Graphic,
      Game
    };
  class	ILibrary
  {
  public:
    virtual LibraryType	getLibraryType() const = 0;
  };
}

#endif /* !ILIBRARY_HH_ */
