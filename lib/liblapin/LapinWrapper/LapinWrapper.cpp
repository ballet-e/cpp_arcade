//
// LapinWrapper.cpp for cpp_arcade in /home/wurmel_a/rendu/cpp_arcade/lib/libopengl
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Mon Apr  3 22:07:33 2017 Arnaud WURMEL
// Last update Sat Apr  8 01:47:17 2017 Arnaud WURMEL
//

#include <map>
#include <utility>
#include "LapinHelper.hh"
#include "LapinWrapper.hh"

static t_bunny_response	loopGame(void *data)
{
  Arcade::LapinWrapper	*wrapper;
  t_color	background_color;
  t_bunny_position	pos;

  wrapper = static_cast<Arcade::LapinWrapper *>(data);
  if (wrapper->_game->shouldRender())
    {
      background_color.full = BLACK;
      Arcade::LapinHelper::setPixArrayColor(wrapper->_root, background_color);
      Arcade::LapinHelper::setPixArrayColor(wrapper->_game_pix, background_color);
      wrapper->_game->render();
      bunny_blit(&wrapper->_window->buffer, &wrapper->_root->clipable, NULL);
      pos.x = (1200 - wrapper->getDrawableWidth()) / 2;
      pos.y = 100;
      if (wrapper->_game->gameState() == Arcade::IGame::PLAYING)
	bunny_blit(&wrapper->_window->buffer, &wrapper->_game_pix->clipable, &pos);
      bunny_display(wrapper->_window);
    }
  return (GO_ON);
}

static t_bunny_response	keyGame(t_bunny_event_state sta,
				t_bunny_keysym sym,
				void *data)
{
  Arcade::LapinWrapper	*wrapper;
  std::map<unsigned int, Arcade::Event::EventType>	keyMapping;
  std::map<unsigned int, Arcade::ExitStatus>	libMapping;

  keyMapping.insert(std::make_pair(BKS_UP, Arcade::Event::AKEY_UP));
  keyMapping.insert(std::make_pair(BKS_DOWN, Arcade::Event::AKEY_DOWN));
  keyMapping.insert(std::make_pair(BKS_LEFT, Arcade::Event::AKEY_LEFT));
  keyMapping.insert(std::make_pair(BKS_RIGHT, Arcade::Event::AKEY_RIGHT));
  libMapping.insert(std::make_pair(BKS_2, Arcade::ExitStatus::PrevLib));
  libMapping.insert(std::make_pair(BKS_3, Arcade::ExitStatus::NextLib));
  libMapping.insert(std::make_pair(51, Arcade::ExitStatus::PrevGame));
  libMapping.insert(std::make_pair(BKS_5, Arcade::ExitStatus::NextGame));
  libMapping.insert(std::make_pair(BKS_9, Arcade::ExitStatus::BackMenu));
  if (sta == GO_UP)
    return (GO_ON);
  wrapper = static_cast<Arcade::LapinWrapper *>(data);
  if (sym == BKS_ESCAPE)
    {
      wrapper->setExitStatus(Arcade::ExitStatus::Exit);
      return (EXIT_ON_SUCCESS);
    }
  if (sym == BKS_8)
    wrapper->_game->initGame();
  if (libMapping.find(sym) != libMapping.end())
    {
      wrapper->setExitStatus(libMapping[sym]);
      return EXIT_ON_SUCCESS;
    }
  if (keyMapping.find(sym) != keyMapping.end())
    wrapper->_game->eventListener(Arcade::Event(keyMapping[sym]));
  return (GO_ON);
}

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

      wrapper->_screen.enterChar(alpha[value]);
    }
  else if (sym == BKS_DELETE || sym == BKS_BACKSPACE)
    wrapper->_screen.enterChar(-1);
  else if (sym == BKS_SPACE)
    wrapper->_screen.enterChar(' ');
  return (GO_ON);
}

static t_bunny_response	loopStartMenu(void *data)
{
  Arcade::LapinWrapper	*wrapper;
  t_color		background_color;

  background_color.full = 0;
  wrapper = static_cast<Arcade::LapinWrapper *>(data);
  if (wrapper->getGamePath().size() > 0 && wrapper->getLibraryPath().size() > 0 &&
      wrapper->getPseudo().size() > 0)
    return EXIT_ON_SUCCESS;
  Arcade::LapinHelper::setPixArrayColor(wrapper->_root, background_color);
  wrapper->drawTitle();
  wrapper->_screen.render(wrapper);
  bunny_blit(&wrapper->_window->buffer, &wrapper->_root->clipable, NULL);
  bunny_display(wrapper->_window);
  return (GO_ON);
}

Arcade::LapinWrapper::LapinWrapper()
{
  _game_pix = NULL;
  _game = NULL;
  _root = NULL;
  _window = NULL;
  _font = bunny_load_pixelarray("Ressources/font.png");
}

bool	Arcade::LapinWrapper::renderWindowStart()
{
  int	ret;

  if (createWindow(1200, 900) == false)
    return false;
  bunny_set_key_response(&keyStartMenu);
  bunny_set_loop_main_function(&loopStartMenu);
  ret = bunny_loop(this->_window, 50, this);
  bunny_stop(_window);
  _window = NULL;
  return ret == EXIT_ON_SUCCESS;
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

void	Arcade::LapinWrapper::drawTitle()
{
  std::string	text;

  setText("Arcade", 10, Arcade::ElementPosition::CENTER, 15, ABLUE);
  if (_screen.getLibraryPath().size() == 0)
    text = "Choisir une bibliotheque pour lancer le jeu";
  else if (_screen.getGamePath().size() == 0)
    text = "Choisir un jeu";
  else
    text = "Entrez votre pseudo";
  setText(text, 120, Arcade::ElementPosition::CENTER, 15, AWHITE);
}

Arcade::ExitStatus	Arcade::LapinWrapper::renderWindowGame(unsigned int width,
							       unsigned int height,
							       Arcade::IGame *game)
{
  if (createWindow(width, height) == false ||
      (_game_pix = bunny_new_pixelarray(600, 600)) == NULL)
    return Arcade::ExitStatus::Exit;
  _status = Arcade::ExitStatus::Exit;
  _game = game;
  _game->setUpGraphics(this);
  bunny_set_key_response(&keyGame);
  bunny_set_loop_main_function(&loopGame);
  bunny_loop(_window, 60, this);
  bunny_stop(_window);
  _window = NULL;
  return _status;
}

bool	Arcade::LapinWrapper::setPixel(unsigned int x, unsigned int y,
				       unsigned int color)
{
  t_color	colors[9];
  t_bunny_position	pos;

  getColors(colors);
  pos.x = x;
  pos.y = y;
  Arcade::LapinHelper::setPixel(_game_pix, pos, colors[color % 9]);
  return true;
}

void	Arcade::LapinWrapper::getColors(t_color colors[9]) const
{
  colors[ABLACK].full = BLACK;
  colors[AGREEN] = Arcade::LapinHelper::colorFromARGB(39, 174, 96);
  colors[AGREY] = Arcade::LapinHelper::colorFromARGB(120, 120, 120);
  colors[ACYAN] = Arcade::LapinHelper::colorFromARGB(52, 152, 219);
  colors[AYELLOW] = Arcade::LapinHelper::colorFromARGB(241, 196, 15);
  colors[ARED] = Arcade::LapinHelper::colorFromARGB(231, 76, 60);
  colors[APINK] = Arcade::LapinHelper::colorFromARGB(142, 68, 173);
  colors[AWHITE] = Arcade::LapinHelper::colorFromARGB(255, 255, 255);
  colors[ABLUE] = Arcade::LapinHelper::colorFromARGB(41, 128, 185);
}

void	Arcade::LapinWrapper::setText(std::string const& to_print, unsigned int y,
				      Arcade::ElementPosition const& mode,
				      unsigned int fontSize,
				      Arcade::Colors const& fontColor,
				      Arcade::Colors const& backgroundColor)
{
  t_bunny_position	text_pos;
  t_bunny_position	square_pos;
  t_color		colors[9];
  size_t		writing_size;

  static_cast<void>(fontSize);
  writing_size = (to_print.size() * 18) + to_print.size();
  text_pos.y = y;
  text_pos.x = 5;
  if (mode == Arcade::ElementPosition::CENTER)
    text_pos.x = (1200 - writing_size) / 2;
  else if (mode == Arcade::ElementPosition::LEFT_CENTER)
    text_pos.x = 580 - writing_size;
  else if (mode == Arcade::ElementPosition::RIGHT_CENTER)
    text_pos.x = 620;
  else if (mode == Arcade::ElementPosition::RIGHT)
    text_pos.x = 1180 - writing_size;
  if (_font == NULL)
    return ;
  getColors(colors);
  square_pos.x = text_pos.x - 1;
  square_pos.y = text_pos.y - 1;
  Arcade::LapinHelper::drawRectangle(_root, square_pos, writing_size + 2, 20,
				     colors[backgroundColor]);
  Arcade::LapinHelper::setText(to_print.c_str(), _root,
			       _font, text_pos, colors[fontColor]);
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
  return _screen.getLibraryPath();
}

std::string const&	Arcade::LapinWrapper::getGamePath() const
{
  return _screen.getGamePath();;
}

std::string const&	Arcade::LapinWrapper::getPseudo() const
{
  return _screen.getPseudo();
}

Arcade::LibraryType	Arcade::LapinWrapper::getLibraryType() const
{
  return (Arcade::LibraryType::GRAPHIC);
}

void	Arcade::LapinWrapper::setExitStatus(Arcade::ExitStatus const& status)
{
  _status = status;
}

Arcade::LapinWrapper::~LapinWrapper() {}
