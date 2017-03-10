//
// main.cpp for cpp_arcade in /home/wurmel/rendu/cpp_arcade
// 
// Made by Arnaud WURMEL
// Login   <wurmel_a@epitech.net>
// 
// Started on  Thu Mar  9 16:27:05 2017 Arnaud WURMEL
// Last update Fri Mar 10 16:56:23 2017 Arnaud WURMEL
//

#include <iostream>

static void	display_ascii(void)
{
  std::cout << "    ___                        __   " << std::endl;
  std::cout << "   /   |  ______________ _____/ /__ " << std::endl;
  std::cout << "  / /| | / ___/ ___/ __ `/ __  / _ \\" << std::endl;
  std::cout << " / ___ |/ /  / /__/ /_/ / /_/ /  __/" << std::endl;
  std::cout << "/_/  |_/_/   \\___/\\__,_/\\__,_/\\___/ " << std::endl;
  std::cout << "\033[0m" << std::endl;
}

int	main(void)
{
  display_ascii();
  std::cerr << "[Arcade] Loading...\t\033[32mOK\033[0m" << std::endl;
  return 0;
}
