#include "ta.hpp"
#include <random>
TA::TA(){
  appeased = false;
}

char TA::get_move(){
  srand(time(NULL));
  std::random_device rd; // obtain a random number from hardware
  std::mt19937 eng(rd()); // seed the generator
  std::uniform_real_distribution<> distr(0, 1); // define the range
  float rf = distr(eng);
  char c;
  if( rf > .75){
    c = 'w';
  }else if( rf > .5){
    c = 'a';
  }else if( rf > .25){
    c = 's';
  }else{
    c = 'd';
  }
  //c = 'w';
  return c;
}

void TA::set_location(int r, int c){
  xPos = c;
  yPos = r;
};

int TA::get_row(){
  return yPos;
}

int TA::get_col(){
  return xPos;
}

void TA::set_appeased(bool b){
  appeased = b;
}

bool TA::get_appeased(){
  return appeased;
}
