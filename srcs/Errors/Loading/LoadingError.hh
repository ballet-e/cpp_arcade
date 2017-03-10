//
// LoadingError.hh for Arcade in /home/wurmel/rendu/cpp_arcade/srcs/Errors
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Fri Mar 10 20:32:12 2017 Arnaud WURMEL
// Last update Fri Mar 10 20:38:59 2017 Arnaud WURMEL
//

#ifndef LOADINGERROR_HH_
# define LOADINGERROR_HH_

# include <string>
# include <exception>

namespace Arcade
{
  class	LoadingError : public std::exception
  {
  public:
    LoadingError(std::string const&);
    LoadingError(const char *);
    ~LoadingError();

  public:
    virtual char const*	what() const throw();

  private:
    std::string	_what;
  };
}

#endif /* !LOADINGERROR_HH_ */
