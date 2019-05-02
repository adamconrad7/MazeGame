#ifndef _ta
#define _ta
#include "MazePerson.hpp"

class TA: public Mazeperson{
  int xPos;
  int yPos;
  bool appeased;
public:
  TA();
  TA(int, int);
  char get_move();
  void set_location(int, int);
  int get_row();
  int get_col();
  void set_appeased(bool);
  bool get_appeased();
};

#endif
