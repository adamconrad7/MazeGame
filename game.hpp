#ifndef _game
#define _game
#include "mazelevel.hpp"

class Game{
  std::vector<Mazelevel*> levels;
public:
  Game(std::ifstream&, int, int, int);
  std::vector<Mazelevel*>& getlevels();
 // ~Game();
  //Mazelevel(const char* arr[], int, int);
};

#endif
