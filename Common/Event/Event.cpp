//
// Event.cpp for arcade in /home/wurmel/rendu/cpp_arcade/Common
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Mon Mar 13 13:05:14 2017 Arnaud WURMEL
// Last update Mon Mar 13 13:10:15 2017 Arnaud WURMEL
//

#include <iostream>
#include "Event.hh"

Arcade::Event::Event(Arcade::Event::EventType const& type) : _type(type)
{

}

Arcade::Event::EventType const&	Arcade::Event::getType() const
{
  return (_type);
}

Arcade::Event::~Event() {}
