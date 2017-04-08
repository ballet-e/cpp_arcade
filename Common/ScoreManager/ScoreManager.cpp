//
// ScoreManager.cpp for arcade in /home/wurmel/rendu/cpp_arcade/Common
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Tue Mar 14 20:23:24 2017 Arnaud WURMEL
// Last update Sat Apr  8 15:59:51 2017 Arnaud WURMEL
//

#include <cstring>
#include <algorithm>
#include <fstream>
#include "ScoreManager.hpp"

Arcade::ScoreManager::ScoreManager()
{

}

bool	Arcade::ScoreManager::loadScoreForGame(std::string const& gameName)
{
  Arcade::ScoreManager::FileHeader	fileHeader;
  Arcade::ScoreManager::ScoreRow	scoreRow;

  if (openFile(gameName, false) == false)
    return false;
  _scoreList.clear();
  _file.read(reinterpret_cast<char *>(&fileHeader), sizeof(Arcade::ScoreManager::FileHeader));
  if (checkFileHeader(fileHeader, gameName) == false)
    {
      std::cerr << "Wrong score file format maybe corrupted. Ignored" << std::endl;
      _file.close();
      return false;
    }
  while (true)
    {
      _file.read(reinterpret_cast<char *>(&scoreRow), sizeof(Arcade::ScoreManager::ScoreRow));
      if (!_file)
	break;
      _scoreList.push_back(scoreRow);
    }
  _file.close();
  std::sort(_scoreList.begin(), _scoreList.end(), Arcade::ScoreManager::sortVector);
  return true;
}

bool	Arcade::ScoreManager::sortVector(Arcade::ScoreManager::ScoreRow const& first, Arcade::ScoreManager::ScoreRow const& second)
{
  return (first.score > second.score);
}

void	Arcade::ScoreManager::addScoreForGame(std::string const& game,
					      std::string const& pseudo,
					      unsigned int value)
{
  Arcade::ScoreManager::ScoreRow	score;

  if (openFile(game, true) == false)
    {
      std::cerr << "Can't add score for : " << game << std::endl;
      return ;
    }
  std::strncpy(score.pseudo, pseudo.c_str(), 20);
  score.score = value;
  _file.write(reinterpret_cast<char *>(&score), sizeof(Arcade::ScoreManager::ScoreRow));
  _file.close();
}

std::vector<Arcade::ScoreManager::ScoreRow> const&	Arcade::ScoreManager::getScoreForGame(std::string const& gameName)
{
  loadScoreForGame(gameName);
  return (_scoreList);
}

bool	Arcade::ScoreManager::checkFileHeader(Arcade::ScoreManager::FileHeader const& fileHeader,
					      std::string const& gameName) const
{
  if (gameName.compare(fileHeader.gameName) || fileHeader.magicNumber != MAGIC_NUMBER_SCORE)
    return false;
  return true;
}

bool	Arcade::ScoreManager::openFile(std::string const& gameName,
				       bool writeMode)
{
  std::string	filepath;

  filepath = "./scores/" + gameName + ".score";
  if (writeMode == false)
    _file.open(filepath, std::fstream::in | std::fstream::binary);
  else
    _file.open(filepath, std::fstream::out | std::fstream::binary | std::fstream::binary | std::fstream::app);
  if (!_file.is_open())
    return false;
  if (writeMode && _file.tellg() == 0)
    {
      Arcade::ScoreManager::FileHeader	fileHeader;

      std::strncpy(fileHeader.gameName, gameName.c_str(), 20);
      fileHeader.magicNumber = MAGIC_NUMBER_SCORE;
      _file.write((char *)&fileHeader, sizeof(Arcade::ScoreManager::FileHeader));
    }
  return true;
}

Arcade::ScoreManager::~ScoreManager() {}
