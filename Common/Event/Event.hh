//
// Event.hh for arcade in /home/wurmel/rendu/cpp_arcade/Common
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Mon Mar 13 12:55:00 2017 Arnaud WURMEL
// Last update Thu Mar 30 15:33:21 2017 Victorien Fischer
//

#ifndef EVENT_HH_
# define EVENT_HH_

namespace	Arcade
{
  class		Event
  {
  public:
    enum	EventType
      {
	AKEY_UP,
	AKEY_DOWN,
	AKEY_LEFT,
	AKEY_RIGHT,
	AKEY_SPACE
      };

  public:
    Event(EventType const&);
    ~Event();

  public:
    EventType const&	getType() const;

  private:
    EventType	_type;
  };
}

#endif /* !EVENT_HH_ */
