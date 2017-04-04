//
// LapinWrapper.cpp for cpp_arcade in /home/wurmel_a/rendu/cpp_arcade/lib/libopengl
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Mon Apr  3 22:07:33 2017 Arnaud WURMEL
// Last update Tue Apr  4 13:09:19 2017 Arnaud WURMEL
//

#include "LapinHelper.hh"
#include "LapinWrapper.hh"

static t_bunny_response	keyStartMenu(t_bunny_event_state sta,
				     t_bunny_keysym sym,
				     void *data)
{
  Arcade::LapinWrapper	*wrapper;

  if (sta == GO_UP)
    return (GO_ON);
  wrapper = static_cast<Arcade::LapinWrapper *>(data);
  if (sym == BKS_ESCAPE)
    return (EXIT_ON_ERROR);
  else if (sym == BKS_RETURN)
    wrapper->_screen.enterKey();
  else if (sym == BKS_UP)
    wrapper->_screen.upKey();
  else if (sym == BKS_DOWN)
    wrapper->_screen.downKey();
  else if (sym >= BKS_A && sym <= BKS_Z)
    {
      std::string	alpha = "abcdefghijklmnopqrstuvwxyz";
      int		value = static_cast<int>(sym) - static_cast<int>(BKS_A);
      
      wrapper->_screen.enterChar(value);
    }
  return (GO_ON);
}

static t_bunny_response	loopStartMenu(void *data)
{
  Arcade::LapinWrapper	*wrapper;
  t_color		background_color;

  background_color.full = 0;
  wrapper = static_cast<Arcade::LapinWrapper *>(data);
  Arcade::LapinHelper::setPixArrayColor(wrapper->_root, background_color);
  wrapper->_screen.render(wrapper);
  bunny_blit(&wrapper->_window->buffer, &wrapper->_root->clipable, NULL);
  bunny_display(wrapper->_window);
  return (GO_ON);
}

Arcade::LapinWrapper::LapinWrapper()
{
  _root = NULL;
  _window = NULL;
  _library_path = "";
  _game_path = "";
  _pseudo = "";
  _font = bunny_load_pixelarray("Ressources/font.png");
}

bool	Arcade::LapinWrapper::renderWindowStart()
{
  if (createWindow(1200, 900) == false)
    return false;
  bunny_set_key_response(&keyStartMenu);
  bunny_set_loop_main_function(&loopStartMenu);
  return bunny_loop(this->_window, 50, this) == EXIT_ON_SUCCESS;
}

bool	Arcade::LapinWrapper::createWindow(unsigned int width, unsigned int height)
{
  if (_window)
    {
      bunny_stop(_window);
      _window = NULL;
    }
  _window = bunny_start(width, height, 0, "LapinWrapper");
  if (_window == NULL)
    return false;
  if (_root)
    {
      bunny_delete_clipable(&_root->clipable);
      _root = NULL;
    }
  _root = createPixelArray(width, height);
  if (_root == NULL)
    return false;
  return true;
}

void	Arcade::LapinWrapper::renderWindowGame(unsigned int width, unsigned int height,
					       Arcade::IGame *game)
{

}

bool	Arcade::LapinWrapper::setPixel(unsigned int x, unsigned int y,
				       unsigned int color)
{

}

void	Arcade::LapinWrapper::setText(std::string const& to_print, unsigned int y,
				      Arcade::ElementPosition const& mode,
				      unsigned int fontSize,
				      Arcade::Colors const& fontColor,
				      Arcade::Colors const& backgroundColor)
{
  t_bunny_position	text_pos;
  t_color		test;

  text_pos.y = y;
  text_pos.x = 0;
  if (_font == NULL)
    return ;
  test.full = WHITE;
  Arcade::LapinHelper::setText(to_print.c_str(), _root,
			       _font, text_pos, test);
}

t_bunny_pixelarray	*Arcade::LapinWrapper::createPixelArray(unsigned int width,
								unsigned int height)
{
  t_bunny_pixelarray	*pix;

  pix = bunny_new_pixelarray(width, height);
  return pix;
}

unsigned int		Arcade::LapinWrapper::getDrawableHeight() const
{
  return (600);
}

unsigned int		Arcade::LapinWrapper::getDrawableWidth() const
{
  return (600);
}

std::string const&	Arcade::LapinWrapper::getLibraryPath() const
{
  return _library_path;
}

std::string const&	Arcade::LapinWrapper::getGamePath() const
{
  return _game_path;
}

std::string const&	Arcade::LapinWrapper::getPseudo() const
{
  return _pseudo;
}

Arcade::LibraryType	Arcade::LapinWrapper::getLibraryType() const
{
  return (Arcade::LibraryType::GRAPHIC);
}

Arcade::LapinWrapper::~LapinWrapper() {}
