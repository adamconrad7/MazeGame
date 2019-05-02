#ifndef _player
#define _player
#include <string>
#include "MazePerson.hpp"
class Player: public Mazeperson{
  int xPos;
  int yPos;
  int nSkills;
public:
  Player();
  Player(int, int);
  char get_move();
  void set_location(int, int);
  int get_row();
  int get_col();
  char get_input(std::string prompt, char c1, char c2, char c3, char c4);
  void addskill();
  int getNskills();
  void loseskills(int);
};

#endif
