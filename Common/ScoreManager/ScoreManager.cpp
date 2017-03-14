//
// ScoreManager.cpp for arcade in /home/wurmel/rendu/cpp_arcade/Common
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Tue Mar 14 20:23:24 2017 Arnaud WURMEL
// Last update Tue Mar 14 21:01:48 2017 Arnaud WURMEL
//

#include "ScoreManager.hpp"

Arcade::ScoreManager::ScoreManager()
{

}

bool	Arcade::ScoreManager::loadScoreForGame(std::string const& gameName)
{
  Arcade::ScoreManager::FileHeader	fileHeader;
  Arcade::ScoreManager::ScoreRow	scoreRow;

  _scoreList.clear();
  _file.read(reinterpret_cast<char *>(&fileHeader), sizeof(Arcade::ScoreManager::FileHeader));
  if (checkFileHeader(fileHeader, gameName) == false)
    {
      std::cout << "Wrong score file format maybe corrupted. Ignored" << std::endl;
      _file.close();
      return false;
    }
  while (_file.eof() == false)
    {
      _file.read(reinterpret_cast<char *>(&scoreRow), sizeof(Arcade::ScoreManager::ScoreRow));
      _scoreList.push_back(std::make_pair(scoreRow.pseudo, scoreRow.score));
    }
  _file.close();
  return true;
}

std::vector<std::pair<std::string, unsigned int> > const&	Arcade::ScoreManager::getScoreForGame(std::string const& gameName)
{
  loadScoreForGame(gameName);
  return (_scoreList);
}

bool	Arcade::ScoreManager::checkFileHeader(Arcade::ScoreManager::FileHeader const& fileHeader,
					      std::string const& gameName) const
{
  if (gameName.compare(fileHeader.gameName) || fileHeader.magicNumber != MAGIC_NUMBER)
    return false;
  return true;
}

bool	Arcade::ScoreManager::openFile(std::string const& gameName,
				       bool writeMode)
{
  filepath = "./game/" + gameName + ".score";
  if (writeMode == false)
    _file.open(filepath, std::fstream::in | std::fstream::binary);
  else
    _file.open(filepath, std::fstream::out | std::fstream::binary);
  if (!file.is_open())
    return false;
  return true;
}

Arcade::ScoreManager::~ScoreManager() {}

int	main(void)
{
  Arcade::ScoreManager	score;

  return (0);
}
