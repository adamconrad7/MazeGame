#include "game.hpp"
#include <iostream>
#include <fstream>


/*********************************************************************
** Function:
** Description:
** Parameters:
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
/*********************************************************************
** Function: game constructor
** Description: Constructs game class
** Parameters: Infile stream, number of levels, number of rows, number of columns.
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
Game::Game(std::ifstream& infile, int n, int r, int c){
  for(int i=0; i<n; i++){//loop for each mazelevel. Needs to 1. make new char array. 2. construct mazelevel. 3.pushback to levels.
    char** newarr = new char*[r];//2d char array///////leak here
    for(int j=0; j<r; j++){
      newarr[j] = new char[c];//1d char array////////leak here
      char twat;
      infile.get(twat);//remove newline
      for(int k=0; k<c; k++){
        char car;
        infile.get(car);
        newarr[j][k] = car;///////leak here
      }
    }
    Mazelevel* m = new Mazelevel(newarr, r, c);//need to delete
    levels.push_back(m);
    for(int i =0; i<r+1; i++){
      delete [] newarr[i];
    }
    delete [] newarr;
   }
}


/*********************************************************************
** Function: getlevels
** Description: Returns a vector of Mazelevel pointers
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
std::vector<Mazelevel*>& Game::getlevels(){
  return levels;
}
//
// Game::~Game(){
// for(int i=0; i<levels.size(); i++){
//      delete levels[i];
//  }
// }
