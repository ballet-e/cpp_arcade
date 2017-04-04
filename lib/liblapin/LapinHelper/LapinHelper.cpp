//
// LapinHelper.cpp for  in /home/wurmel_a/rendu/cpp_arcade/lib/liblapin
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Tue Apr  4 12:23:23 2017 Arnaud WURMEL
// Last update Tue Apr  4 13:22:54 2017 Arnaud WURMEL
//

#include "LapinHelper.hh"

void	Arcade::LapinHelper::setPixArrayColor(t_bunny_pixelarray *pixArray,
					      t_color color)
{
  t_bunny_position	idx;
  t_color		*pix;

  pix = static_cast<t_color *>(pixArray->pixels);
  idx.y = 0;
  while (idx.y < pixArray->clipable.clip_height)
    {
      idx.x = 0;
      while (idx.x < pixArray->clipable.clip_width)
	{
	  pix[idx.x + (idx.y * pixArray->clipable.clip_width)].full = color.full;
	  ++idx.x;
	}
      idx.y += 1;
    }
}

static void			my_putchar(t_bunny_position pos_2,
					   t_bunny_pixelarray *out,
					   t_bunny_pixelarray *font,
					   int i,
					   t_color replace)
{
  t_color		*font_2;
  t_color		*array;
  unsigned int		color;
  int			w;
  t_bunny_position	pos;

  array = static_cast<t_color *>(out->pixels);
  font_2 = static_cast<t_color *>(font->pixels);
  pos.y = pos_2.y;
  while (pos.y < (pos_2.y + font->clipable.clip_height))
    {
      pos.x = pos_2.x;
      while (pos.x < pos_2.x + 18)
	{
	  w = (((pos.x - pos_2.x) + font->clipable.clip_x_position) +
	       ((pos.y - pos_2.y) * font->clipable.clip_width));
	  color = font_2[w].full;
	  if (color != 0)
	    array[(pos.x + (i * 18)) +
		  (pos.y * out->clipable.clip_width)].full = replace.full;
	  pos.x++;
	}
      pos.y++;
    }
}

void	Arcade::LapinHelper::setText(const char *str, t_bunny_pixelarray *out,
				     t_bunny_pixelarray *fontpng,
				     t_bunny_position pos,
				     t_color color)
{
  t_bunny_position	pos2;
  int			deb;
  int			i;
  int			k;

  k = -1;
  pos2.x = pos.x;
  pos2.y = pos.y;
  while (str[++k] && !(deb = 0))
    {
      i = 0;
      if (str[k] == '\n' && (pos2.x = pos.x))
	pos2.y += fontpng->clipable.clip_height + 1;
      else
	{
	  while ((i + 'A') != str[k] && (i + 'a') != str[k] && i < 26)
	    {
	      deb += 18;
	      ++i;
	    }
	  fontpng->clipable.clip_x_position = deb;
	  if (str[k] && str[k] != ' ' && i != 26)
	    my_putchar(pos2, out, fontpng, pos2.x - pos.x, color);
	  pos2.x++;
	}
    }
}

