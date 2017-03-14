//
// Snake.cpp for Arcade in /home/wurmel/rendu/cpp_arcade/games/libsnake
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Mon Mar 13 16:19:28 2017 Arnaud WURMEL
// Last update Tue Mar 14 16:13:08 2017 Arnaud WURMEL
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
  _hasEat = false;
  _isInit = true;
  _dir = Arcade::Snake::RIGHT;
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
	  if (x == 0 || x + 1 == MAP_WIDTH || y == 0 || y + 1 == MAP_HEIGHT)
	    _map[y][x] = 1;
	  else
	    _map[y][x] = 0;
	  ++x;
	}
      ++y;
    }
  generateFood();
  _body.push_back(std::make_pair(MAP_WIDTH / 2, MAP_HEIGHT / 2));
}

void	Arcade::Snake::generateFood()
{
  std::vector<std::pair<unsigned int, unsigned int> >::const_iterator	it;
  std::pair<unsigned int, unsigned int>	new_pos;
  unsigned int	nb_recur;
  bool		founded;

  founded = false;
  nb_recur = 0;
  while (nb_recur < 1 + _food.size() && !founded)
    {
      founded = true;
      new_pos.first = (rand() % (MAP_WIDTH - 1)) + 1;
      new_pos.second = (rand() % (MAP_HEIGHT - 1)) + 1;
      it = _food.begin();
      while (it != _food.end())
	{
	  if ((*it).first == new_pos.first && (*it).second == new_pos.second)
	    founded = false;
	  ++it;
	}
      if (founded == true)
	_food.push_back(new_pos);
      ++nb_recur;
    }
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
	    drawSquare(square_size, Arcade::Colors::RED, x * square_size, y * square_size);
	  ++x;
	}
      ++y;
    }
  std::vector<std::pair<unsigned int, unsigned int> >::iterator	it = _body.begin();

  while (it != _body.end())
    {
      drawSquare(square_size, Arcade::Colors::YELLOW, (*it).first * square_size, (*it).second * square_size);
      ++it;
    }
  it = _food.begin();
  while (it != _food.end())
    {
      drawSquare(square_size, Arcade::Colors::CYAN, (*it).first * square_size, (*it).second * square_size);
      ++it;
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

bool	Arcade::Snake::eatFood()
{
  std::vector<std::pair<unsigned int, unsigned int> >::iterator	it;
  std::pair<unsigned int, unsigned int>& head = (*_body.begin());

  it = _food.begin();
  while (it != _food.end())
    {
      if (head.first == (*it).first && head.second == (*it).second)
	{
	  _food.erase(it);
	  return (true);
	}
      else
	++it;
    }
  return (false);
}

void	Arcade::Snake::moveSnake()
{
  int	x_shift;
  int	y_shift;
  std::pair<unsigned int, unsigned int>	new_elem;
  unsigned int	i;

  x_shift = 0;
  y_shift = 0;
  if (_dir == Arcade::Snake::UP)
    y_shift = -1;
  else if (_dir == Arcade::Snake::DOWN)
    y_shift = 1;
  else if (_dir == Arcade::Snake::LEFT)
    x_shift = -1;
  else if (_dir == Arcade::Snake::RIGHT)
    x_shift = 1;
  i = _body.size() - 1;
  new_elem = _body.back();
  while (i >= 1)
    {
      _body[i] = _body[i - 1];
      --i;
    }
  if (_map[(*_body.begin()).second + y_shift][(*_body.begin()).first + x_shift] != 1)
    {
      (*_body.begin()).second += y_shift;
      (*_body.begin()).first += x_shift;
    }
  if (_hasEat)
    {
      _body.push_back(new_elem);
       _hasEat = false;
    }
  if (eatFood())
    {
      generateFood();
      _hasEat = true;
      _score += 1;
    }
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
  if ((50 - _score) != 0)
    {
      if (_frame % (50 - _score) <= 0)
	{
	  _frame = 1;
	  return true;
	}
    }
  _frame += 1;
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
      _frame = 1;
    }
}

Arcade::Snake::~Snake() {}
