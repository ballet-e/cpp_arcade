//
// Snake.cpp for Arcade in /home/wurmel/rendu/cpp_arcade/games/libsnake
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Mon Mar 13 16:19:28 2017 Arnaud WURMEL
// Last update Tue Mar 14 00:04:19 2017 Arnaud WURMEL
//

#include <iostream>
#include "Snake.hh"
#include "IGraphic.hh"

Arcade::Snake::Snake()
{
  _score = 0;
  _frame = 0;
  _isInit = false;
  initGame();
}

void	Arcade::Snake::initGame()
{
  initMap();
  _isInit = true;
}

void	Arcade::Snake::initMap()
{
  unsigned int	x;
  unsigned int	y;

  y = 0;
  while (y < MAP_HEIGHT)
    {
      x = 0;
      while (x < MAP_WIDTH)
	{
	  _map[y][x] = 0;
	  ++x;
	}
      ++y;
    }
  _map[MAP_HEIGHT / 2][MAP_WIDTH / 2] = 2;
}

void	Arcade::Snake::drawSquare(unsigned int size, unsigned int color,
				  unsigned int pos_x, unsigned int pos_y)
{
  unsigned int	x;
  unsigned int	y;

  y = 0;
  while (y < size)
    {
      x = 0;
      while (x < size)
	{
	  if (y == 0 || y + 1 == size || x == 0 || x + 1 == size)
	    _graphic_library->setPixel(pos_x + x, pos_y + y, 0);
	  else
	    _graphic_library->setPixel(pos_x + x, pos_y + y, color);
	  ++x;
	}
      ++y;
    }
}

void	Arcade::Snake::showMap()
{
  unsigned int	x;
  unsigned int	y;
  unsigned int	square_size;

  square_size = (_graphic_library->getDrawableHeight() - (2 * MAP_HEIGHT))  / MAP_HEIGHT;
  y = 0;
  while (y < MAP_HEIGHT)
    {
      x = 0;
      while (x < MAP_WIDTH)
	{
	  if (_map[y][x] == 0)
	    drawSquare(square_size, Arcade::Colors::GREY, x * square_size, y * square_size);
	  else if (_map[y][x] == 1)
	    drawSquare(square_size, Arcade::Colors::GREEN, x * square_size, y * square_size);
	  else if (_map[y][x] == 2)
	    drawSquare(square_size, Arcade::Colors::YELLOW, x * square_size, y * square_size);
	  ++x;
	}
      ++y;
    }
}

void	Arcade::Snake::setUpGraphics(Arcade::IGraphic *ref)
{
  _graphic_library = ref;
}

Arcade::LibraryType	Arcade::Snake::getLibraryType() const
{
  return (Arcade::GAME);
}

void	Arcade::Snake::getSnakePosition(unsigned int& y, unsigned int& x) const
{
  y = 0;
  while (y < MAP_HEIGHT)
    {
      x = 0;
      while (x < MAP_WIDTH)
	{
	  if (_map[y][x] == 2)
	    return ;
	  ++x;
	}
      ++y;
    }
  
}

void	Arcade::Snake::moveSnake()
{
  unsigned int	x;
  unsigned int	y;

  getSnakePosition(y, x);
  _map[y][x] = 0;
  if (_dir == Arcade::Snake::LEFT && x > 0)
    _map[y][x - 1] = 2;
  else if (_dir == Arcade::Snake::RIGHT && x + 1 < MAP_WIDTH)
    _map[y][x + 1] = 2;
  else if (_dir == Arcade::Snake::UP && y > 0)
    _map[y - 1][x] = 2;
  else if (_dir == Arcade::Snake::DOWN && y < MAP_HEIGHT)
    _map[y + 1][x] = 2;
}

void	Arcade::Snake::render()
{
  if (!_isInit)
    initGame();
  moveSnake();
  _graphic_library->setText(std::string("Niveau: ") + std::to_string(_score / 10), 10, Arcade::TextMode::LEFT);
  _graphic_library->setText(std::string("Snake"), 10, Arcade::TextMode::CENTER, 25);
  _graphic_library->setText(std::string("Score: ") + std::to_string(_score), 10, Arcade::TextMode::RIGHT);
  showMap();
}

bool	Arcade::Snake::shouldRender()
{
  _frame += 1;
  if ((50 - _score) != 0)
    {
      if (_frame % (50 - _score) <= 0)
	{
	  _frame = 0;
	  return true;
	}
    }
  return false;
}

void	Arcade::Snake::eventListener(Event const& e)
{
  bool	need_to_render = false;

  if (e.getType() == Arcade::Event::KEY_UP)
    {
      if (_dir != Arcade::Snake::UP)
	need_to_render = true;
      _dir = Arcade::Snake::UP;
    }
  else if (e.getType() == Arcade::Event::KEY_DOWN)
    {
      if (_dir != Arcade::Snake::DOWN)
	need_to_render = true;
      _dir = Arcade::Snake::DOWN;
    }
  else if (e.getType() == Arcade::Event::KEY_LEFT)
    {
      if (_dir != Arcade::Snake::LEFT)
	need_to_render = true;
      _dir = Arcade::Snake::LEFT;
    }
  else if (e.getType() == Arcade::Event::KEY_RIGHT)
    {
      if (_dir != Arcade::Snake::RIGHT)
	need_to_render = true;
      _dir = Arcade::Snake::RIGHT;
    }
  if (need_to_render)
    {
      render();
      _frame = 0;
    }
}

Arcade::Snake::~Snake() {}
