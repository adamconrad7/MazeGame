#include <iostream>
#include "OpenSpace.hpp"

Openspace::Openspace(char c){
  symbol = c;
  isStart = false;
  isEnd = false;
  hasPlayer = false;
  hasTA = false;
  hasSkill = false;
  hasInstructor = false;
  if(symbol == '@'){
    isStart = true;
    isEnd = false;
  }else if(symbol == '^'){
    isStart = false;
    isEnd = true;
  }else if(symbol == '%'){
    hasInstructor = true;
  }
}



Openspace::~Openspace(){
}

/*********************************************************************
** Function: Basic getters and setters that are aptly desribed by their name.
** Description: Either modifies a boolean field or returns one.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
void Openspace::set_hasInstructor(bool b){
  hasInstructor = b;
}

bool Openspace::getInstructor(){
  return hasInstructor;
}

void Openspace::set_has_explorer(bool b){
  hasPlayer = b;
  //symbol = 'X';
}

bool Openspace::has_explorer(){
  return hasPlayer;
}

void Openspace::set_has_TA(bool b){
  hasTA = b;
}

bool Openspace::has_TA(){
  return hasTA;
}

void Openspace::set_is_start(bool b){
  isStart = b;
}

bool Openspace::is_start(){
  return isStart;
}

void Openspace::set_is_end(bool b){
  isEnd = b;
}

bool Openspace::is_end(){
  return isEnd;
}

void Openspace::set_has_skill(bool b){
  hasSkill = b;
}

bool Openspace::get_skill(){
  return hasSkill;
}
