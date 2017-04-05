//
// LapinHelper.hh for  in /home/wurmel_a/rendu/cpp_arcade/lib/liblapin
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Tue Apr  4 12:22:00 2017 Arnaud WURMEL
// Last update Tue Apr  4 14:58:56 2017 Arnaud WURMEL
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
    static void	drawRectangle(t_bunny_pixelarray *, t_bunny_position,
			      int, int, t_color);
    static t_color	colorFromARGB(char r, char g, char b);
    static void	setPixel(t_bunny_pixelarray *, t_bunny_position, t_color);
  };
}

#endif /* !LAPINHELPER_HH_ */
