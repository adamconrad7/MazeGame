#ifndef _wall
#define _wall
#include <iostream>
#include "MazeLocation.hpp"

class Wall: public Mazelocation{
public:
  ~Wall() {};
  bool is_occupiable()  {return false;}
  char get_display_character()  {return '#';}
  void set_has_explorer(bool) {};
  virtual Wall* clone() const {return(new Wall(*this));};
  //bool has_explorer() {return true;}
};

#endif
