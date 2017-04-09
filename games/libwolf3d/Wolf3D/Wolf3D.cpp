//
// Wolf3D.cpp for cpp_arcade in /home/wurmel_a/rendu/cpp_arcade/games/libwolf3d
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Thu Apr  6 16:37:34 2017 Arnaud WURMEL
// Last update Sun Apr  9 16:03:51 2017 Arnaud WURMEL
//

#include <math.h>
#include "Wolf3D.hh"

Arcade::Wolf3D::Wolf3D()
{
  initGame();
  _keyBinding.insert(std::make_pair(Arcade::Event::EventType::AKEY_UP, std::bind(&Arcade::Wolf3D::forward, this)));
  _keyBinding.insert(std::make_pair(Arcade::Event::EventType::AKEY_DOWN, std::bind(&Arcade::Wolf3D::backward, this)));
  _keyBinding.insert(std::make_pair(Arcade::Event::EventType::AKEY_LEFT, std::bind(&Arcade::Wolf3D::rotateLeft, this)));
  _keyBinding.insert(std::make_pair(Arcade::Event::EventType::AKEY_RIGHT, std::bind(&Arcade::Wolf3D::rotateRight, this)));
}

void	Arcade::Wolf3D::initGame()
{
  _loader.deleteMap();
  _map = _loader.getMap("Ressources/Wolf3D/map.wolf");
  if (_map.size() > 0)
    _p.pos = _loader.getPlayerPosition();
  _p.angle = 0.0;
  _render = true;
  _map_width = _loader.getMapWidth();
  _map_height = _loader.getMapHeight();
}

void	Arcade::Wolf3D::setUpGraphics(Arcade::IGraphic *graphic)
{
  _render = true;
  _graphic = graphic;
}

void	Arcade::Wolf3D::setUpPseudo(std::string const& pseudo)
{
  _pseudo = pseudo;
}

void	Arcade::Wolf3D::drawSquare(unsigned int x, unsigned int y,
				   Arcade::Position const& size,
				   unsigned int color)
{
  Arcade::Position	idx;

  idx.y = 0;
  while (idx.y < size.y)
    {
      idx.x = 0;
      while (idx.x < size.x)
	{
	  _graphic->setPixel(x + idx.x, y + idx.y, color);
	  ++idx.x;
	}
      ++idx.y;
    }
}

void	Arcade::Wolf3D::render()
{
  double	size_wall;
  unsigned int	i;
  unsigned int	k;
  double	k_wall;

  i = 0;
  while (i < _graphic->getDrawableWidth())
    {
      k = 0;
      k_wall = getWallSize(i);
      size_wall = (_graphic->getDrawableHeight() / (2 * k_wall));
      while (k < (_graphic->getDrawableHeight() / 2) - size_wall)
	{
	  _graphic->setPixel(i, k, Arcade::Colors::ACYAN);
	  ++k;
	}
      while (k < (_graphic->getDrawableHeight() / 2) + size_wall)
	{
	  _graphic->setPixel(i, k, Arcade::Colors::AWHITE);
	  ++k;
	}
      while (k < _graphic->getDrawableHeight())
	{
	  _graphic->setPixel(i, k, Arcade::Colors::AGREY);
	  ++k;
	}
      ++i;
    }
}

bool	Arcade::Wolf3D::shouldRender()
{
  if (_render)
    {
      _render = false;
      return true;
    }
  return false;
}

Arcade::IGame::GameState	Arcade::Wolf3D::gameState() const
{
  return (Arcade::IGame::GameState::PLAYING);
}

unsigned int	Arcade::Wolf3D::getMapWidth() const
{
  return SCREEN_WIDTH;
}

unsigned int	Arcade::Wolf3D::getMapHeight() const
{
  return SCREEN_HEIGHT;
}

void	Arcade::Wolf3D::eventListener(Arcade::Event const& e)
{
  if (_keyBinding.find(e.getType()) != _keyBinding.end())
    {
      _keyBinding[e.getType()]();
      _render = true;
    }
}

double	Arcade::Wolf3D::getWallSize(double pos)
{
  double	width;
  double	x;
  double	y;
  double	k;
  double	d_x;
  double	d_y;

  width = _graphic->getDrawableWidth();
  y = ((P * ((width / 2) - pos)) / width);
  d_x = (D * cos(_p.angle)) - (y * sin(_p.angle));
  d_y = (D * sin(_p.angle)) + (y * cos(_p.angle));
  k = 0;
  x = _p.pos.x;
  y = _p.pos.x;
  while (x < _map_width && y < _map_width)
    {
      k = k + 0.025;
      x = _p.pos.x + k * d_x;
      y = _p.pos.y + k * d_y;
      if (x >= _map_width || y >= _map_height || x < 0 || y < 0)
	return k;
      if (x < _map_width && y < _map_height &&
	  _map[static_cast<int>(x) + (static_cast<int>(y) * _map_width)]->_type != FREE)
	return k;
    }
  return k;
}

void	Arcade::Wolf3D::forward()
{
  double	x_player;
  double	y_player;

  x_player = _p.pos.x + (0.025 * cos(_p.angle));
  y_player = _p.pos.y + (0.025 * sin(_p.angle));
  if (_map[static_cast<int>(x_player) + (static_cast<int>(y_player) * _map_width)]->_type != FREE)
    {
      return ;
    }
  _p.pos.x = x_player;
  _p.pos.y = y_player;
}

void	Arcade::Wolf3D::backward()
{
  double	x_player;
  double	y_player;

  x_player = _p.pos.x - (0.025 * cos(_p.angle));
  y_player = _p.pos.y - (0.025 * sin(_p.angle));
  if (_map[static_cast<int>(x_player) + (static_cast<int>(y_player) * _map_width)]->_type != FREE)
    {
      return ;
    }
  _p.pos.x = x_player;
  _p.pos.y = y_player;
}

void	Arcade::Wolf3D::rotateLeft()
{
  double	tmp;

  _p.angle += 0.015;
  tmp = _p.angle;
  if (tmp < 0)
    tmp = -tmp;
  if (tmp >= 2 * M_PI)
    _p.angle = 0;
}

void	Arcade::Wolf3D::rotateRight()
{
  double	tmp;

  _p.angle -= 0.015;
  tmp = _p.angle;
  if (tmp < 0)
    tmp = -tmp;
  if (tmp >= 2 * M_PI)
    _p.angle = 0;
}

Arcade::LibraryType	Arcade::Wolf3D::getLibraryType() const
{
  return (Arcade::GAME);
}

Arcade::Wolf3D::~Wolf3D()
{
}
