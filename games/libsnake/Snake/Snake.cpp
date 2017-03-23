//
// Snake.cpp for Arcade in /home/wurmel/rendu/cpp_arcade/games/libsnake
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Mon Mar 13 16:19:28 2017 Arnaud WURMEL
// Last update Thu Mar 23 19:58:15 2017 Arnaud WURMEL
//

#include <iostream>
#include "Protocol.hpp"
#include "Snake.hh"
#include "ScoreManager.hpp"
#include "IGraphic.hh"

Arcade::Snake::Snake() : _map(MAP_HEIGHT)
{
  _score = 0;
  _frame = 0;
  _isInit = false;
  _graderMode = true;
  _pseudo = "Player";
  initGame();
}

void	Arcade::Snake::initGame()
{
  _map.clear();
  initMap();
  _hasEat = false;
  _isInit = true;
  _playing = true;
  _end = false;
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
	    _map[y].push_back(1);
	  else
	    _map[y].push_back(0);
	  ++x;
	}
      ++y;
    }
  generateFood();
  _body.push_back(std::make_pair(MAP_WIDTH / 2, MAP_HEIGHT / 2));
  _body.push_back(std::make_pair((MAP_WIDTH / 2) - 1, MAP_HEIGHT / 2));
  _body.push_back(std::make_pair((MAP_WIDTH / 2) - 2, MAP_HEIGHT / 2));
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
      new_pos.first = (rand() % (MAP_WIDTH - 2)) + 1;
      new_pos.second = (rand() % (MAP_HEIGHT - 2)) + 1;
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
	    drawSquare(square_size, Arcade::Colors::BLACK, x * square_size, y * square_size);
	  else if (_map[y][x] == 1)
	    drawSquare(square_size, Arcade::Colors::RED, x * square_size, y * square_size);
	  ++x;
	}
      ++y;
    }
  std::vector<std::pair<unsigned int, unsigned int> >::iterator	it = _body.begin();

  while (it != _body.end())
    {
      if (it == _body.begin())
	drawSquare(square_size, Arcade::Colors::GREEN, (*it).first * square_size, (*it).second * square_size);
      else
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
  _graderMode = false;
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
  (*_body.begin()).second += y_shift;
  (*_body.begin()).first += x_shift;
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
  if (checkSnakeColision() == false)
    {
      _playing = false;
      _end = true;
      saveScore();
    }
}

void	Arcade::Snake::saveScore() const
{
  Arcade::ScoreManager	scoreManager;

  scoreManager.addScoreForGame("Nibbler", _pseudo, _score);
}

void	Arcade::Snake::render()
{
  if (!_isInit)
    initGame();
  if (_playing)
    moveSnake();
  _graphic_library->setText(std::string("Niveau: ") + std::to_string(_score / 10), 10, Arcade::ElementPosition::LEFT);
  _graphic_library->setText(std::string("Nibbler"), 10, Arcade::ElementPosition::CENTER, 25);
  _graphic_library->setText(std::string("Score: ") + std::to_string(_score), 10, Arcade::ElementPosition::RIGHT);
  if (!_end)
    showMap();
  else
    _graphic_library->setText(std::string("Game Over"), _graphic_library->getDrawableHeight() / 2, Arcade::ElementPosition::CENTER, 25);
}

bool	Arcade::Snake::shouldRender()
{
  if (!_playing || _end)
    return true;
  if ((20 - (_score / 10)) > 0)
    {
      if (_frame % (20 - (_score / 10)) <= 0)
	{
	  _frame = 1;
	  return true;
	}
    }
  else
    return true;
  _frame += 1;
  return false;
}

void	Arcade::Snake::eventListener(Event const& e)
{
  bool	need_to_render = false;

  if (e.getType() == Arcade::Event::KEY_UP && _dir != Arcade::Snake::DOWN)
    {
      if (_dir != Arcade::Snake::UP)
	need_to_render = true;
      _dir = Arcade::Snake::UP;
    }
  else if (e.getType() == Arcade::Event::KEY_DOWN && _dir != Arcade::Snake::UP)
    {
      if (_dir != Arcade::Snake::DOWN)
	need_to_render = true;
      _dir = Arcade::Snake::DOWN;
    }
  else if (e.getType() == Arcade::Event::KEY_LEFT && _dir != Arcade::Snake::RIGHT)
    {
      if (_dir != Arcade::Snake::LEFT)
	need_to_render = true;
      _dir = Arcade::Snake::LEFT;
    }
  else if (e.getType() == Arcade::Event::KEY_RIGHT && _dir != Arcade::Snake::LEFT)
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

bool	Arcade::Snake::checkSnakeColision() const
{
  std::vector<std::pair<unsigned int, unsigned int> >::const_iterator	it;

  it = _body.begin();
  if (_map[(*it).second][(*it).first] != 0)
    return false;
  ++it;
  while (it != _body.end())
    {
      if ((*_body.begin()).first == (*it).first &&
	  (*_body.begin()).second == (*it).second)
	{
	  return false;
	}
      ++it;
    }
  return true;
}

Arcade::IGame::GameState	Arcade::Snake::gameState() const
{
  if (_playing)
    return (Arcade::IGame::PLAYING);
  if (!_playing && !_end)
    return (Arcade::IGame::PAUSED);
  return (Arcade::IGame::ENDED);
}

void	Arcade::Snake::setUpPseudo(std::string const& pseudo)
{
  _pseudo = pseudo;
}

Arcade::Snake::~Snake() {}

/*
** ======================================
**          Mandatory Protocol
** ======================================
*/

void	Arcade::Snake::whereAmI()
{
  struct arcade::WhereAmI	*amI;
  std::vector<std::pair<unsigned int, unsigned int> >::const_iterator	it;

  amI = static_cast<struct arcade::WhereAmI *>(std::malloc(sizeof(struct arcade::WhereAmI) + (sizeof(struct arcade::Position) * _body.size())));
  amI->type = arcade::CommandType::WHERE_AM_I;
  amI->lenght = _body.size();
  it = _body.begin();
  while (it != _body.end())
    {
      amI->position[(it - _body.begin()) % _body.size()].x = (*it).first;
      amI->position[(it - _body.begin()) % _body.size()].y = (*it).second;
      ++it;
    }
  std::cout.write(reinterpret_cast<char *>(amI), sizeof(amI) + (_body.size() * sizeof(struct arcade::Position)));
  std::free(amI);
}

void	Arcade::Snake::getMap()
{
  struct arcade::GetMap	*map;
  unsigned int		y;
  unsigned int		x;

  map = static_cast<struct arcade::GetMap *>(std::malloc(sizeof(struct arcade::GetMap) + (sizeof(arcade::TileType) * MAP_HEIGHT * MAP_WIDTH)));
  if (map != NULL)
    {
      map->width = MAP_WIDTH;
      map->height = MAP_HEIGHT;
      map->type = arcade::CommandType::GET_MAP;
      y = 0;
      while (y < MAP_HEIGHT)
	{
	  x = 0;
	  while (x < MAP_WIDTH)
	    {
	      if (_map[y][x] == 0)
		map->tile[x + (y * MAP_WIDTH)] = arcade::TileType::EMPTY;
	      else
		map->tile[x + (y * MAP_WIDTH)] = arcade::TileType::BLOCK;
	      ++x;
	    }
	  ++y;
	}
      std::cout.write(reinterpret_cast<char *>(map), sizeof(struct arcade::GetMap) + (sizeof(arcade::TileType) * MAP_HEIGHT * MAP_WIDTH));
      std::free(map);
    }
}

void	Arcade::Snake::goUp()
{

}

void	Arcade::Snake::goDown()
{
  
}

void	Arcade::Snake::goLeft()
{
}

void	Arcade::Snake::goRight()
{

}

void	Arcade::Snake::goForward()
{
  std::cerr << "Not used for snake" << std::endl;
}

void	Arcade::Snake::makeShoot()
{
  std::cerr << "Not used for snake" << std::endl;
}

void	Arcade::Snake::illegal()
{
  std::cerr << "Not used for snake" << std::endl;
}

void	Arcade::Snake::playRound()
{

}
