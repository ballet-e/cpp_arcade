//
// LIBLAPINWrapper.hpp for arcade in /home/ballet/CPP/cpp_arcade/lib/liblapin/LIBLAPINWrapper/
//
// Made by Ballet Erwan
// Login   <erwan.ballet@epitech.eu>
//
// Started on  Sun Mar 12 07:18:50 2017 Ballet Erwan
// Last update Mon Mar 13 17:27:27 2017 Ballet Erwan
//

#ifndef LIBLAPINWRAPPER_HH_
# define LIBLAPINWRAPPER_HH_

# include "IGraphic.hh"
# include "lapin.h"

namespace Arcade
{
  class	LIBLAPINWrapper : public Arcade::IGraphic
  {
  public:
    LIBLAPINWrapper();
    ~LIBLAPINWrapper();
  public:
    bool	renderWindowStart();
    bool	createWindow(unsigned int, unsigned int);
    bool	drawSquare64x64(unsigned int, unsigned int, unsigned int);
    LibraryType	getLibraryType() const;

  private:
    t_bunny_window  *win;
  };
}

#endif /* !LIBLAPINWRAPPER_HH_ */
