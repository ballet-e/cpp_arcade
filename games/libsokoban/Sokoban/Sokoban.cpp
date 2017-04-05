//
// Sokoban.cpp for cpp_arcade in /home/vicky/Bureau/EPITECH/tek2-2/C++/cpp_arcade/games/libsokoban/Sokoban
// 
// Made by Victorien Fischer
// Login   <victorien.fischer@epitech.eu>
// 
// Started on  Wed Apr  5 19:05:51 2017 Victorien Fischer
// Last update Thu Apr  6 01:07:03 2017 Victorien Fischer
//

#include "Sokoban.hh"
#include "ScoreManager.hpp"
#include "IGraphic.hh"

Arcade::Sokoban::Sokoban()
{
  _score = 0;
  _level = 0;
  _pseudo = "Player";
}

void	Arcade::Sokoban::render()
{
}

bool	Arcade::Sokoban::shouldRender()
{
  return (true);
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
Arcade::LibraryType	Arcade::Sokoban::getLibraryType() const
{
  return (Arcade::GAME);
}

Arcade::Sokoban::~Sokoban() {}
