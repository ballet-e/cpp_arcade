//
// Sokoban.cpp for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libsokoban/Sokoban
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Wed Apr  5 19:05:51 2017 Victorien Fischer
// Last update Thu Apr  6 16:34:20 2017 Victorien Fischer
//

#include "Sokoban.hh"
#include "ScoreManager.hpp"
#include "IGraphic.hh"

Arcade::Sokoban::Sokoban()
{
  _score = 0;
  _level = 0;
  _pseudo = "Player";
  _shouldRender = true;
  _playing = true;
  _success = false;
  _gameover = false;
}

/*
** ===== > RENDERING
*/
void	Arcade::Sokoban::render()
{
  _graphic_library->setText(std::string("Niveau: ") + std::to_string(_level), 10, Arcade::ElementPosition::LEFT);
  _graphic_library->setText(std::string("Sokoban"), 10, Arcade::ElementPosition::CENTER, 25);
  _graphic_library->setText(std::string("Pousse: ") + std::to_string(_score), 10, Arcade::ElementPosition::RIGHT);
  if (_gameover)
    _graphic_library->setText(std::string("Game Over"), _graphic_library->getDrawableHeight() / 2, Arcade::ElementPosition::CENTER, 25);
  if (_success)
    _graphic_library->setText(std::string("You Won !"), _graphic_library->getDrawableHeight() / 2, Arcade::ElementPosition::CENTER, 25);
}

bool	Arcade::Sokoban::shouldRender()
{
  if (!_playing || (_gameover || _success))
    return (true);
  if (_shouldRender)
    return (true);
  return (false);
}

void	Arcade::Sokoban::drawCase(Arcade::Case c) const
{
  unsigned int	x;
  unsigned int	y;
  unsigned int	size_h;
  unsigned int	size_w;

  size_h = _graphic_library->getDrawableHeight() / MAP_HEIGHT;
  size_w = _graphic_library->getDrawableHeight() / MAP_WIDTH;
  y = 0;
  while (y < size_h)
    {
      x = 0;
      while (x < size_w)
	{
	  _graphic_library->setPixel((size_w * c.getX()) + x,
				     (size_h * c.getY()) + y,
				     c.getColor());
	  x += 1;
	}
      y += 1;
    }
}

void	Arcade::Sokoban::showMap() const
{
  std::vector<Arcade::Case>::const_iterator	it;

  it = _map.begin();
  while (it != _map.end())
    {
      drawCase(*it);
      it++;
    }
}

/*
** ===== > EVENTS
*/
void	Arcade::Sokoban::eventListener(Event const &event)
{
}

/*
** ===== > SCORE
*/
void	Arcade::Sokoban::saveScore() const
{
  Arcade::ScoreManager	scoreManager;

  scoreManager.addScoreForGame("sokoban", _pseudo, _score);
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
  return (MAP_WIDTH);
}

unsigned int			Arcade::Sokoban::getMapHeight() const
{
  return (MAP_HEIGHT);
}

Arcade::Sokoban::~Sokoban() {}
