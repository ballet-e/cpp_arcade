//
// SolarFox.cpp for Arcade in /home/ballet/CPP/cpp_arcade/games/libsolarfox/SolarFox/
//
// Made by Ballet Erwan
// Login   <erwan.ballet@epitech.eu>
//
// Started on  Tue Apr  4 11:17:48 2017 Ballet Erwan
// Last update Wed Apr  5 16:43:29 2017 Erwan BALLET
//

#include <iostream>
#include "Bullet.hh"
#include "Enemy.hh"
#include "Protocol.hpp"
#include "SolarFox.hh"
#include "ScoreManager.hpp"
#include "IGraphic.hh"

Arcade::SolarFox::SolarFox()
{
  _isInit = false;
  _graderMode = true;
  _pseudo = "Player";
}

void	Arcade::SolarFox::setUpGraphics(Arcade::IGraphic *ref)
{
  _graderMode = false;
  _graphic_library = ref;
}

Arcade::LibraryType	Arcade::SolarFox::getLibraryType() const
{
  return (Arcade::GAME);
}

void			Arcade::SolarFox::setUpPseudo(std::string const& pseudo)
{
  _pseudo = pseudo;
}

void			Arcade::SolarFox::eventListener(Event const& e)
{
  if (!_validatePosition)
    return ;
  if (e.getType() == Arcade::Event::AKEY_UP && _dir != Arcade::Bullet::DOWN)
    {
      _validatePosition = false;
      _dir = Arcade::Bullet::UP;
    }
  else if (e.getType() == Arcade::Event::AKEY_DOWN && _dir != Arcade::Bullet::UP)
    {
      _validatePosition = false;
      _dir = Arcade::Bullet::DOWN;
    }
  else if (e.getType() == Arcade::Event::AKEY_LEFT && _dir != Arcade::Bullet::RIGHT)
    {
      _validatePosition = false;
      _dir = Arcade::Bullet::LEFT;
    }
  else if (e.getType() == Arcade::Event::AKEY_RIGHT && _dir != Arcade::Bullet::LEFT)
    {
      _validatePosition = false;
      _dir = Arcade::Bullet::RIGHT;
    }
}

void	Arcade::SolarFox::render()
{
  //int	i;
  
  _validatePosition = true;
  /*if (!_isInit)
    initGame();
  while (i < 4)
    {
      moove_enemy(_Enemy[i]);
      i++;
    }
  if (_playing)
    moveSolarFox(); */
}

bool	Arcade::SolarFox::shouldRender()
{
  return (true);
}

Arcade::IGame::GameState	Arcade::SolarFox::gameState() const
{
  return (Arcade::IGame::ENDED);
}

void	whereAmI() {}

void	getMap() {}

void	goUp() {}

void	goDown() {}

void	goLeft() {}

void	goRight() {}

void	goForward() {}

void	makeShoot() {}

void	illegal() {}

void	playRound() {}
