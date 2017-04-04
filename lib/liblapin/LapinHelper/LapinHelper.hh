//
// LapinHelper.hh for  in /home/wurmel_a/rendu/cpp_arcade/lib/liblapin
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Tue Apr  4 12:22:00 2017 Arnaud WURMEL
// Last update Tue Apr  4 13:22:52 2017 Arnaud WURMEL
//

#ifndef LAPINHELPER_HH_
# define LAPINHELPER_HH_

# include "lapin.h"

namespace	Arcade
{
  class	LapinHelper
  {
  public:
    static void	setPixArrayColor(t_bunny_pixelarray *pix,
				 t_color color);

    static void	setText(const char *, t_bunny_pixelarray *,
			t_bunny_pixelarray *, t_bunny_position,
			t_color);

    static t_color	colorFromARGB(char a, char r, char g, char b);
  };
}

#endif /* !LAPINHELPER_HH_ */
