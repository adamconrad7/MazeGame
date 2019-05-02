#ifndef _mazeperson
#define _mazeperson

class Mazeperson{
public:
  virtual char get_move() =0;
  virtual void set_location(int, int) = 0;
  virtual int get_row() =0;
  virtual int get_col() =0;
};

#endif
