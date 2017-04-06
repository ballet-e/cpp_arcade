//
// Wolf3D.cpp for cpp_arcade in /home/wurmel_a/rendu/cpp_arcade/games/libwolf3d
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Thu Apr  6 16:37:34 2017 Arnaud WURMEL
// Last update Thu Apr  6 17:32:36 2017 Arnaud WURMEL
//

#include "Wolf3D.hh"

Arcade::Wolf3D::Wolf3D()
{

}

void	Arcade::Wolf3D::initGame()
{
  
}

void	Arcade::Wolf3D::setUpGraphics(Arcade::IGraphic *graphic)
{
  _graphic = graphic;
}

void	Arcade::Wolf3D::setUpPseudo(std::string const& pseudo)
{
  _pseudo = pseudo;
}

void	Arcade::Wolf3D::render()
{

}

bool	Arcade::Wolf3D::shouldRender()
{
  return true;
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
  static_cast<void>(e);
}

Arcade::LibraryType	Arcade::Wolf3D::getLibraryType() const
{
  return (Arcade::GAME);
}

Arcade::Wolf3D::~Wolf3D() {}
