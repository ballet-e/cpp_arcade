//
// NCursesWrapper.cpp for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/lib/libncurses/Wrapper
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Wed Mar 29 22:19:52 2017 Victorien Fischer
// Last update Tue Apr  4 01:48:46 2017 Victorien Fischer
//

#include <thread>
#include <chrono>
#include "NCursesWrapper.hh"

Arcade::NCursesWrapper::NCursesWrapper()
{
  initscr();
  cbreak();
  noecho();
  start_color();
  init_color(ABLACK + 8, 0, 0, 0);
  init_color(AGREEN + 8, 39, 174, 96);
  init_color(AGREY + 8, 120, 120, 120);
  init_color(ACYAN + 8, 52, 152, 219);
  init_color(AYELLOW + 8, 241, 196, 15);
  init_color(ARED + 8, 231, 76, 60);
  init_color(APINK + 8, 231, 76, 60);
  init_color(AWHITE + 8, 255, 255, 255);
  _row = 0;
  _col = 0;
  _window = NULL;
}

bool	Arcade::NCursesWrapper::renderWindowStart()
{
  int	key;

  deleteWindow();
  createWindow(80, 80);
  drawWindow();
  while (_window)
    {
      if ((key = wgetch(_window)) != ERR)
	{
	  if (keyboardHandler(key))
	    drawWindow();
	  if (_screen.getGamePath().size() > 0 &&
	      _screen.getLibraryPath().size() > 0)
	    deleteWindow();
	}
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  return (_screen.getLibraryPath().size() && _screen.getGamePath().size());
}

void	Arcade::NCursesWrapper::renderWindowGame(unsigned int width, unsigned int height, IGame *game)
{
  int	key;

  deleteWindow();
  createWindow(width, height);
  game->setUpGraphics(this);
  while (_window)
    {
      if ((key = wgetch(_window)) != ERR)
	{
	  if (key == 27)
	    {
	      deleteWindow();
	      return ;
	    }
	  if (key == KEY_UP)
	    game->eventListener(Event(Arcade::Event::AKEY_UP));;
	  if (key == KEY_DOWN)
	    game->eventListener(Event(Arcade::Event::AKEY_DOWN));;
	  if (key == KEY_LEFT)
	    game->eventListener(Event(Arcade::Event::AKEY_LEFT));;
	  if (key == KEY_RIGHT)
	    game->eventListener(Event(Arcade::Event::AKEY_RIGHT));;
	  if (game->gameState() == Arcade::IGame::PLAYING)
	    wrefresh(_window);
	}
      if (game->shouldRender())
	{
	  wclear(_window);
	  game->render();
	  if (game->gameState() == Arcade::IGame::PLAYING)
	    wrefresh(_window);
	}
      std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

bool	Arcade::NCursesWrapper::setPixel(unsigned int x, unsigned int y, unsigned int p)
{
  return (true);
}

Arcade::LibraryType	Arcade::NCursesWrapper::getLibraryType() const
{
  return (Arcade::GRAPHIC);
}

void	Arcade::NCursesWrapper::setText(std::string const &to_print,
					unsigned int y,
					Arcade::ElementPosition const &mode,
					unsigned int fontSize,
					Arcade::Colors const &fontColor,
					Arcade::Colors const &backgroundColor)
{
  int		id_pair;
  unsigned int	x;

  id_pair = createPair(fontColor + 8, backgroundColor + 8);
  x = 1;
  if (mode == Arcade::ElementPosition::CENTER)
    x = (_row - to_print.length())/2;
  else if (mode == Arcade::ElementPosition::RIGHT)
    x = (_row - to_print.length() - 1);
  else if (mode == Arcade::ElementPosition::RIGHT_CENTER)
    x = (_row / 2) - 50;
  else if (mode == Arcade::ElementPosition::LEFT_CENTER)
    x = (_row / 2) - (to_print.length() + 50);
  wmove(_window, (y / 20), x);
  wattron(_window, COLOR_PAIR(id_pair));
  wprintw(_window, to_print.c_str());
  wattroff(_window, COLOR_PAIR(id_pair));
}

short		Arcade::NCursesWrapper::createPair(short font,
						   short back)
{
  short		id;
  std::map<short, std::pair<short, short>>::iterator	it;

  id = 1;
  it = _colorpair.begin();
  while (it != _colorpair.end())
    {
      id += 1;
      if ((it->second).first == font && (it->second).second == back)
	return (it->first);
      it++;
    }
  init_pair(id, font, back);
  _colorpair.insert(std::pair<short, std::pair<short, short>>
		    (id, std::pair<short, short>(font, back)));
  return (id);
}

unsigned int	Arcade::NCursesWrapper::getDrawableHeight() const
{
  return (_row);
}

unsigned int	Arcade::NCursesWrapper::getDrawableWidth() const
{
  return (_col);
}

std::string const	&Arcade::NCursesWrapper::getLibraryPath() const
{
  return (_screen.getLibraryPath());
}

std::string const	&Arcade::NCursesWrapper::getGamePath() const
{
  return (_screen.getGamePath());
}

std::string const	&Arcade::NCursesWrapper::getPseudo() const
{
  return (_screen.getPseudo());
}

void	Arcade::NCursesWrapper::drawTitle()
{
  std::string	name("Arcade");
  std::string	lib("Choisir une bibliothèque pour lancer le jeu");
  std::string	game("Choisir un jeu");
  std::string	pseudo("Entrez votre pseudo");
  
  mvwprintw(_window, 4, (_row - name.length())/2, name.c_str());
  if (_screen.getLibraryPath().size() == 0)
    mvwprintw(_window, 7, (_row - lib.length())/2, lib.c_str());
  else if (_screen.getGamePath().size() == 0)
    mvwprintw(_window, 7, (_row - game.length())/2, game.c_str());
  else
    mvwprintw(_window, 7, (_row - pseudo.length())/2, pseudo.c_str());
}

bool	Arcade::NCursesWrapper::createWindow(unsigned int width, unsigned int height)
{
  _row = width;
  _col = height;
  resizeterm(_row, _col);
  _window = newwin(width, height, 0, 0);
  nodelay(_window, TRUE);
  keypad(_window, TRUE);
  return (true);
}

bool	Arcade::NCursesWrapper::deleteWindow()
{
  if (_window)
    {
      delwin(_window);
      _window = NULL;
      return (true);
    }
  return (false);
}

void	Arcade::NCursesWrapper::drawWindow()
{
  wclear(_window);
  drawTitle();
  _screen.render(this);
  wrefresh(_window);
}

bool	Arcade::NCursesWrapper::keyboardHandler(int e)
{
  if (e == 27)
    {
      deleteWindow();
      return (false);
    }
  if (e == 10)
    _screen.enterKey();
  if (e == KEY_UP)
    _screen.upKey();
  if (e == KEY_DOWN)
    _screen.downKey();
  return (true);
}

Arcade::NCursesWrapper::~NCursesWrapper()
{
  endwin();
}
