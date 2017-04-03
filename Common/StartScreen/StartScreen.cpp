//
// StartScreen.cpp for arcade in /home/wurmel/rendu/cpp_arcade/lib/libsfml
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Thu Mar 16 01:08:33 2017 Arnaud WURMEL
// Last update Mon Apr  3 19:23:23 2017 Arnaud WURMEL
//

#include "IGraphic.hh"
#include "StartScreen.hpp"

Arcade::StartScreen::StartScreen()
{
  loadLibrary();
}

void	Arcade::StartScreen::render(Arcade::IGraphic *graphic)
{
  std::vector<Arcade::Selectable *>::iterator	it;

  it = _item_list.begin();
  while (it != _item_list.end())
    {
      if (_current_pos == it)
      	(*it)->renderObject(graphic, true);
      else
      	(*it)->renderObject(graphic);
      ++it;
    }
  getScore(graphic);
}

void	Arcade::StartScreen::getScore(Arcade::IGraphic *graphic)
{
  Arcade::ScoreManager	scoreManager;
  Arcade::Button	*button;
  std::string	text_line;
  size_t	pos;

  if (_library_path.size() && !_game_path.size())
    {
      if ((*_current_pos)->getType() == Arcade::Button::SELECT)
  	{
	  button = dynamic_cast<Button *>((*_current_pos));
  	  std::string game_name = button->getTitle();
	  
  	  if (game_name.find("lib_arcade_") == 0)
  	    game_name.erase(0, 11);
  	  if ((pos = game_name.find(".so")) != std::string::npos)
  	    game_name.erase(pos);
  	  std::vector<Arcade::ScoreManager::ScoreRow> const&	vec = scoreManager.getScoreForGame(game_name);
  	  std::vector<Arcade::ScoreManager::ScoreRow>::const_iterator	it;

  	  it = vec.begin();
  	  pos = 600;
  	  for (unsigned int i = 0; i < 10 && it != vec.end(); i++) {
  	    text_line = "#" + std::to_string(i + 1) + " ";
  	    text_line = text_line + (*it).pseudo + " : " + std::to_string((*it).score);
  	    graphic->setText(text_line, 250 + ((_button_list.size() + 1) * 32) + (i * 20), Arcade::ElementPosition::CENTER);
  	    ++it;
  	  }
  	}
    }
}

void	Arcade::StartScreen::loadLibrary()
{
  DIR	*dir;
  struct dirent	*dent;
  unsigned int	y;
  std::vector<Button *>::iterator	it;
  std::vector<Selectable *>::iterator	it2;

  it2 = _item_list.begin();
  while (it2 != _item_list.end())
    {
      delete (*it2);
      ++it2;
    }
  _item_list.clear();
  _field_list.clear();
  _button_list.clear();
  dir = opendir(_library_path.size() > 0 ? "./games" : "./lib");
  if (dir == NULL)
    {
      std::cerr << "Can't load libraries directory" << std::endl;
      throw std::exception();
    }
  y = 200;
  while ((dent = readdir(dir)))
    {
      if (dent->d_type == DT_REG && std::string(dent->d_name).find(".so") != std::string::npos && y <= 600)
	{
	  _button_list.push_back(new Arcade::Button(std::string(dent->d_name), y,
						    Arcade::ElementPosition::CENTER,
						    std::bind(&Arcade::StartScreen::buttonSelect,
							      this),
						    Arcade::Button::ButtonType::SELECT));
	  y += 30;
	}
    }
  if (_library_path.size())
    {
      _button_list.push_back(new Arcade::Button("Annuler", y + 50, Arcade::ElementPosition::LEFT_CENTER, std::bind(&Arcade::StartScreen::buttonCancel, this), Arcade::Button::ButtonType::RETURN));
      _button_list.push_back(new Arcade::Button("OK", y + 50, Arcade::ElementPosition::RIGHT_CENTER, std::bind(&Arcade::StartScreen::buttonValidate, this), Arcade::Button::ButtonType::VALIDATE));
    }
  else
    _button_list.push_back(new Arcade::Button("OK", y + 50, Arcade::ElementPosition::CENTER, std::bind(&Arcade::StartScreen::buttonValidate, this), Arcade::Button::ButtonType::VALIDATE));
  closedir(dir);
  it = _button_list.begin();
  while (it != _button_list.end())
    {
      _item_list.push_back((*it));
      ++it;
    }
  _button_list.back()->enable(false);
  _current_pos = _item_list.begin();
}

void	Arcade::StartScreen::upKey()
{
  if (_current_pos == _item_list.begin())
    _current_pos = _item_list.end();
  --_current_pos;
}

void	Arcade::StartScreen::downKey()
{
  ++_current_pos;
  if (_current_pos == _item_list.end())
    _current_pos = _item_list.begin();
}

void	Arcade::StartScreen::enterKey()
{
  Arcade::Button	*button;

  if (_current_pos != _item_list.end())
    {
      button = dynamic_cast<Arcade::Button *>((*_current_pos));
      if (button)
	(button)->makeAction();
    }
}

void	Arcade::StartScreen::enterChar(char c)
{
  if (_current_pos != _item_list.end())
    {
      if ((*_current_pos)->getType() == Arcade::Selectable::UNKNOWN)
	{
	  dynamic_cast<Arcade::TextField *>((*_current_pos))->addChar(c);
	}
    }
}

void	Arcade::StartScreen::buttonValidate()
{
  std::vector<Arcade::Selectable *>::iterator	it;

  it = _item_list.begin();
  while (it != _item_list.end())
    {
      if ((*it)->isSelected())
	{
	  if (_library_path.size() == 0)
	    _library_path = (*it)->getTitle();
	  else if (_game_path.size() == 0)
	    _game_path = (*it)->getTitle();
	  else
	    _pseudo = (*it)->getTitle();
	}
      ++it;
    }
  if (_game_path.size() == 0 || _library_path.size() == 0)
    loadLibrary();
  else if (_pseudo.size() == 0)
    {
      it = _item_list.begin();
      while (it != _item_list.end())
	{
	  delete (*it);
	  ++it;
	}
      _item_list.clear();
      _button_list.clear();
      _field_list.clear();
      _button_list.push_back(new Arcade::Button("OK", 250, Arcade::ElementPosition::CENTER, std::bind(&Arcade::StartScreen::buttonValidate, this), Arcade::Button::ButtonType::VALIDATE));
      _field_list.push_back(new Arcade::TextField(200, Arcade::ElementPosition::CENTER));
      _item_list.push_back(_field_list.back());
      _item_list.push_back(_button_list.back());
      _current_pos = _item_list.begin();
    }
}

void	Arcade::StartScreen::buttonCancel()
{
  _library_path.clear();
  _game_path.clear();
  loadLibrary();
}

void	Arcade::StartScreen::buttonSelect()
{
  std::vector<Arcade::Button *>::iterator	it;

  it = _button_list.begin();
  if ((*_current_pos)->isSelected() == false)
    {
      while (it != _button_list.end())
	{
	  (*it)->setSelected(false);
	  ++it;
	}
      (*_current_pos)->setSelected(true);
    }
  else
    (*_current_pos)->setSelected(false);
  _button_list.back()->enable((*_current_pos)->isSelected());
}

std::string const&	Arcade::StartScreen::getLibraryPath() const
{
  return _library_path;
}

std::string const&	Arcade::StartScreen::getGamePath() const
{
  return _game_path;
}

std::string const&	Arcade::StartScreen::getPseudo() const
{
  return _pseudo;
}

Arcade::StartScreen::~StartScreen()
{
  std::vector<Arcade::Selectable *>::iterator	it;

  for (it = _item_list.begin(); it != _item_list.end(); it++) {
    delete (*it);
  }
}
