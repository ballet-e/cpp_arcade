//
// Maze.cpp for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libmaze/Maze
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Wed Apr  5 19:05:51 2017 Victorien Fischer
// Last update Sun Apr  9 21:36:55 2017 Arnaud WURMEL
//

#include "Maze.hh"
#include "ScoreManager.hpp"
#include "MapManager.hh"
#include "IGraphic.hh"

Arcade::Maze::Maze() : _mapManager()
{
  _pseudo = "Player";
  initGame();
}

void	Arcade::Maze::initGame()
{
  _move = 0;
  _shouldRender = true;
  _success = false;
  _gameover = false;
  _error = false;
  _errorMsg = "";
  _map = _mapManager.retrieveMap("Ressources/Maze/map");
  checkMap();
  _playing = !_error;
  if (_playing)
    checkEnd();
}

/*
** ===== > CHECKING
*/
void					Arcade::Maze::checkMap()
{
  int					countDestination;
  int					countPlayer;
  std::vector<Arcade::Case *>::iterator	it;

  countDestination = 0;
  countPlayer = 0;
  if (_map.begin() == _map.end())
    {
      _error = true;
      _errorMsg = "Map file is empty or wasn't found.";
      return ;
    }
  it = _map.begin();
  while (it != _map.end())
    {
      if ((*it)->getObstacle())
	{
	  if ((*it)->getObstacle()->getType() == Arcade::Obstacle::PLAYER)
	    countPlayer += 1;
	}
      if ((*it)->getFloor())
	countDestination += ((*it)->getFloor()->getType() == Arcade::Floor::DESTINATION);
      it++;
    }
  if (countDestination != 1)
    {
      _error = true;
      if (countDestination > 1)
	_errorMsg = "Invalid Map : Too much arrival points.";
      else
	_errorMsg = "Invalid Map : Not enough arrival point.";
      return ;
    }
  if (countPlayer != 1)
    {
      _error = true;
      if (countPlayer < 1)
	_errorMsg = "Invalid Map : No player start position.";
      else
	_errorMsg = "Invalid Map : Too much players.";
      return ;
    }
}

void					Arcade::Maze::checkEnd()
{
  std::vector<Arcade::Case *>::iterator	it;

  _success = true;
  it = _map.begin();
  while (it != _map.end())
    {
      if ((*it)->getObstacle())
	if ((*it)->getObstacle()->getType() == Arcade::Obstacle::PLAYER)
	  {
	    if ((*it)->getFloor())
	      {
		if ((*it)->getFloor()->getType() != Arcade::Floor::DESTINATION)
		  _success = false;
	      }
	    else
	      _success = false;
	  }
      it++;
    }
  if (_success)
    _playing = false;
}

/*
** ===== > RENDERING
*/
void	Arcade::Maze::render()
{
  _graphic_library->setText(std::string("Maze"), 10, Arcade::ElementPosition::CENTER, 25);
  _graphic_library->setText(std::string("Moved: ") + std::to_string(_move), 10, Arcade::ElementPosition::RIGHT);
  if (_playing)
    {
      showMap();
      checkEnd();
    }
  if (_gameover)
    _graphic_library->setText(std::string("Game Over"), _graphic_library->getDrawableHeight() / 2, Arcade::ElementPosition::CENTER, 25);
  if (_success)
    _graphic_library->setText(std::string("You Won !"), _graphic_library->getDrawableHeight() / 2, Arcade::ElementPosition::CENTER, 25, Arcade::Colors::AWHITE, Arcade::Colors::AGREEN);
  if (_error)
    _graphic_library->setText(_errorMsg, _graphic_library->getDrawableHeight() / 2, Arcade::ElementPosition::CENTER, 25, Arcade::Colors::ARED, Arcade::Colors::AWHITE);
}

bool	Arcade::Maze::shouldRender()
{
  if (!_playing || (_gameover || _success))
    return (true);
  if (_shouldRender)
    return (true);
  return (false);
}

void	Arcade::Maze::drawCase(Arcade::Case *c) const
{
  unsigned int	x;
  unsigned int	y;
  unsigned int	size_h;
  unsigned int	size_w;

  size_h = _graphic_library->getDrawableHeight() / getMapHeight();
  size_w = _graphic_library->getDrawableHeight() / getMapWidth();
  y = 0;
  while (y < size_h)
    {
      x = 0;
      while (x < size_w)
	{
	  _graphic_library->setPixel((size_w * c->getX()) + x,
				     (size_h * c->getY()) + y,
				     c->getColor());
	  x += 1;
	}
      y += 1;
    }
}

void	Arcade::Maze::showMap() const
{
  std::vector<Arcade::Case *>::const_iterator	it;

  it = _map.begin();
  while (it != _map.end())
    {
      drawCase((*it));
      it++;
    }
}

/*
** ===== > EVENTS
*/
void		Arcade::Maze::eventListener(Event const &e)
{
  Arcade::Case	*player;
  Arcade::Case	*to;

  if (!_playing)
    return ;
  if (!(player = getPlayerCase()))
    return ;
  to = NULL;
  if (e.getType() == Arcade::Event::AKEY_UP)
    to = getPositionCase(player->getX(), player->getY() - 1);
  if (e.getType() == Arcade::Event::AKEY_DOWN)
    to = getPositionCase(player->getX(), player->getY() + 1);
  if (e.getType() == Arcade::Event::AKEY_RIGHT)
    to = getPositionCase(player->getX() + 1, player->getY());
  if (e.getType() == Arcade::Event::AKEY_LEFT)
    to = getPositionCase(player->getX() -1, player->getY());
  if (!to)
    return ;
  if (to->getObstacle())
    return ;
  to->setObstacle(player->getObstacle());
  player->setObstacle(NULL);
  _move += 1;
}

/*
** ===== > SCORE
*/
void	Arcade::Maze::saveScore() const
{
  Arcade::ScoreManager	scoreManager;

  scoreManager.addScoreForGame("maze", _pseudo, _move);
}

/*
** ===== > SETTER
*/
void	Arcade::Maze::setUpPseudo(std::string const &pseudo)
{
  _pseudo = pseudo;
}

void	Arcade::Maze::setUpGraphics(Arcade::IGraphic *ref)
{
  _graphic_library = ref;
}

/*
** ===== > GETTER
*/
Arcade::LibraryType		Arcade::Maze::getLibraryType() const
{
  return (Arcade::GAME);
}

Arcade::IGame::GameState	Arcade::Maze::gameState() const
{
  if (_playing)
    return (Arcade::IGame::PLAYING);
  if (!_playing && !(_gameover || _success))
    return (Arcade::IGame::PAUSED);
  return (Arcade::IGame::ENDED);
}

unsigned int			Arcade::Maze::getMapWidth() const
{
  return (20);
}

unsigned int			Arcade::Maze::getMapHeight() const
{
  return (20);
}

Arcade::Case			*Arcade::Maze::getPositionCase(int x, int y)
{
  std::vector<Arcade::Case *>::iterator	it;

  it = _map.begin();
  while (it != _map.end())
    {
      if ((*it)->getX() == x && (*it)->getY() == y)
	return ((*it));
      it++;
    }
  return (NULL);
}

Arcade::Case			*Arcade::Maze::getPlayerCase()
{
  std::vector<Arcade::Case *>::iterator	it;

  it = _map.begin();
  while (it != _map.end())
    {
      if ((*it)->getObstacle())
	if ((*it)->getObstacle()->getType() == Arcade::Obstacle::PLAYER)
	  return ((*it));
      it++;
    }
  return (NULL);
}

Arcade::Maze::~Maze() {}
