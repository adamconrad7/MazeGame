#include "player.hpp"
#include <iostream>
#include <string>
Player::Player() { nSkills = 0;}

/*********************************************************************
** Function: basic getters/setters that are aptly described by their names.
** Description:
** Parameters:
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
char Player::get_move(){
  std::string str = "Enter which direction you would like to move (WASD)";
  char c = get_input(str, 'w', 'a', 's', 'd');
  return c;
}

void Player::set_location(int r, int c){
  xPos = c;
  yPos = r;
};

int Player::get_row(){
  return yPos;
}

int Player::get_col(){
  return xPos;
}

void Player::addskill(){
  nSkills++;
  std::cout<<"You learned a new programming skill!"<<std::endl;
}

int Player::getNskills(){
  return nSkills;
}

void Player::loseskills(int n){
  nSkills -= n;
}

/*********************************************************************
** Function: get_input
** Description: Prompts and validates user input.
** Parameters: String that contains the prompt, chars that are the acceptable responses.
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
char Player::get_input(std::string prompt, char c1, char c2, char c3, char c4){
  bool flag = false;
  char in = '0';
  do{
    std::cout<<prompt<<std::endl;
    std::cin>> in;
    if(in != c1 && in != c2 && in != c3 && in != c4){
      std::cout<<"Please enter a valid choice."<<std::endl;
      flag = true;
    }else{
      flag = false;
    }
  }while(flag);
  return in;
}
