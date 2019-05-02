#ifndef _openspace
#define _openspace
#include <iostream>
#include "MazeLocation.hpp"

class Openspace: public Mazelocation{
  char symbol;// = ' ';
  bool hasPlayer;
  bool hasTA;
  bool hasSkill;
  bool isStart;
  bool isEnd;
  bool hasInstructor;
public:
  Openspace(char);
  ~Openspace();
  virtual Openspace* clone() const {return(new Openspace(*this));};
  bool is_occupiable() { return true; }
  char get_display_character()  {return symbol;}
  void set_has_explorer(bool);
  bool has_explorer();
  void set_has_TA(bool);
  bool has_TA();
  void set_is_start(bool);
  bool is_start();
  void set_is_end(bool);
  bool is_end();
  void set_has_skill(bool);
  bool get_skill();
  void set_hasInstructor(bool);
  bool getInstructor();
};

#endif
