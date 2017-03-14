//
// ScoreManager.hpp for arcade in /home/wurmel/rendu/cpp_arcade/Common
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Tue Mar 14 20:23:38 2017 Arnaud WURMEL
// Last update Tue Mar 14 21:00:44 2017 Arnaud WURMEL
//

#ifndef SCOREMANAGER_HPP_
# define SCOREMANAGER_HPP_

# include <string>
# include <utility>
# include <vector>
# include <iostream>
# include <fstream>

# define MAGIC_NUMBER 0xAE57

namespace	Arcade
{
  
  class		ScoreManager
  {
  public:
    struct	FileHeader
    {
      char	gameName[20];
      unsigned short	magicNumber;
    } __attribute__((packed));

  public:
    struct	ScoreRow
    {
      char		pseudo[20];
      unsigned int	score;
    };

  public:
    ScoreManager();
    ~ScoreManager();

  public:
    std::vector<std::pair<std::string, unsigned int> > const&	getScoreForGame(std::string const&);
  private:
    bool	openFile(std::string const&, bool);
    bool	loadScoreForGame(std::string const&);
    bool	checkFileHeader(Arcade::ScoreManager::FileHeader const&,
				std::string const&) const;

  private:
    std::vector<std::pair<std::string, unsigned int> >	_scoreList;
    std::fstream					_file;
  };
}

#endif /* !SCOREMANAGER_HPP_ */
