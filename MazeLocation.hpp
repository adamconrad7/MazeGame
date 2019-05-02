#ifndef _mazelocation
#define _mazelocation
#include <iostream>

class Mazelocation{
public:
  virtual ~Mazelocation() {};
  virtual bool is_occupiable()=0;
  virtual char get_display_character()=0;
  virtual Mazelocation* clone() const =0;
      
};

#endif
