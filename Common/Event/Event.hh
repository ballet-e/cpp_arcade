//
// Event.hh for arcade in /home/wurmel/rendu/cpp_arcade/Common
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Mon Mar 13 12:55:00 2017 Arnaud WURMEL
// Last update Mon Mar 13 13:10:02 2017 Arnaud WURMEL
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
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_SPACE
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
