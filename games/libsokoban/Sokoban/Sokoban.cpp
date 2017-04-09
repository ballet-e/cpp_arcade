//
// Sokoban.cpp for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libsokoban/Sokoban
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Wed Apr  5 19:05:51 2017 Victorien Fischer
// Last update Sun Apr  9 21:37:04 2017 Arnaud WURMEL
//

#include "Sokoban.hh"
#include "ScoreManager.hpp"
#include "MapManager.hh"
#include "IGraphic.hh"

Arcade::Sokoban::Sokoban() : _mapManager()
{
  _pseudo = "Player";
  initGame();
}

void	Arcade::Sokoban::initGame()
{
  _push = 0;
  _shouldRender = true;
  _success = false;
  _gameover = false;
  _error = false;
  _errorMsg = "";
  _map = _mapManager.retrieveMap("Ressources/Sokoban/map");
  checkMap();
  _playing = !_error;
  if (_playing)
    checkEnd();
}

/*
** ===== > CHECKING
*/
void					Arcade::Sokoban::checkMap()
{
  int					countStorage;
  int					countBox;
  int					countPlayer;
  std::vector<Arcade::Case *>::iterator	it;

  countStorage = 0;
  countBox = 0;
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
	  if ((*it)->getObstacle()->getType() == Arcade::Obstacle::BOX)
	    countBox += 1;
	  else if ((*it)->getObstacle()->getType() == Arcade::Obstacle::PLAYER)
	    countPlayer += 1;
	}
      if ((*it)->getFloor())
	countStorage += ((*it)->getFloor()->getType() == Arcade::Floor::STORAGE);
      it++;
    }
  if (countStorage != countBox)
    {
      _error = true;
      if (countStorage > countBox)
	_errorMsg = "Invalid Map : Too much storages.";
      else
	_errorMsg = "Invalid Map : Too much boxes.";
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

void					Arcade::Sokoban::checkEnd()
{
  std::vector<Arcade::Case *>::iterator	it;

  _success = true;
  it = _map.begin();
  while (it != _map.end())
    {
      if ((*it)->getObstacle())
	if ((*it)->getObstacle()->getType() == Arcade::Obstacle::BOX)
	  {
	    if ((*it)->getFloor())
	      {
		if ((*it)->getFloor()->getType() != Arcade::Floor::STORAGE)
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
void	Arcade::Sokoban::render()
{
  _graphic_library->setText(std::string("Sokoban"), 10, Arcade::ElementPosition::CENTER, 25);
  _graphic_library->setText(std::string("Pushed: ") + std::to_string(_push), 10, Arcade::ElementPosition::RIGHT);
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

bool	Arcade::Sokoban::shouldRender()
{
  if (!_playing || (_gameover || _success))
    return (true);
  if (_shouldRender)
    return (true);
  return (false);
}

void	Arcade::Sokoban::drawCase(Arcade::Case *c) const
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

void	Arcade::Sokoban::showMap() const
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
void		Arcade::Sokoban::eventListener(Event const &e)
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
    {
      if (to->getObstacle()->getType() != Arcade::Obstacle::BOX)
	return ;
      if (!canPush(to, e))
	return ;
    }
  to->setObstacle(player->getObstacle());
  player->setObstacle(NULL);
}

bool			Arcade::Sokoban::canPush(Arcade::Case *box, Event const &e)
{
  Arcade::Case		*to;

  to = NULL;
  if (e.getType() == Arcade::Event::AKEY_UP)
    to = getPositionCase(box->getX(), box->getY() - 1);
  if (e.getType() == Arcade::Event::AKEY_DOWN)
    to = getPositionCase(box->getX(), box->getY() + 1);
  if (e.getType() == Arcade::Event::AKEY_RIGHT)
    to = getPositionCase(box->getX() + 1, box->getY());
  if (e.getType() == Arcade::Event::AKEY_LEFT)
    to = getPositionCase(box->getX() -1, box->getY());
  if (!to)
    return (false);
  if (to->getObstacle())
    return (false);
  to->setObstacle(box->getObstacle());
  box->setObstacle(NULL);
  _push += 1;
  return (true);
}

/*
** ===== > SCORE
*/
void	Arcade::Sokoban::saveScore() const
{
  Arcade::ScoreManager	scoreManager;

  scoreManager.addScoreForGame("sokoban", _pseudo, _push);
}

/*
** ===== > SETTER
*/
void	Arcade::Sokoban::setUpPseudo(std::string const &pseudo)
{
  _pseudo = pseudo;
}

void	Arcade::Sokoban::setUpGraphics(Arcade::IGraphic *ref)
{
  _graphic_library = ref;
}

/*
** ===== > GETTER
*/
Arcade::LibraryType		Arcade::Sokoban::getLibraryType() const
{
  return (Arcade::GAME);
}

Arcade::IGame::GameState	Arcade::Sokoban::gameState() const
{
  if (_playing)
    return (Arcade::IGame::PLAYING);
  if (!_playing && !(_gameover || _success))
    return (Arcade::IGame::PAUSED);
  return (Arcade::IGame::ENDED);
}

unsigned int			Arcade::Sokoban::getMapWidth() const
{
  return (20);
}

unsigned int			Arcade::Sokoban::getMapHeight() const
{
  return (20);
}

Arcade::Case			*Arcade::Sokoban::getPositionCase(int x, int y)
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

Arcade::Case			*Arcade::Sokoban::getPlayerCase()
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

Arcade::Sokoban::~Sokoban() {}
