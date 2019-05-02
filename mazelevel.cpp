#include <iostream>
#include <vector>
#include "mazelevel.hpp"
#include "OpenSpace.hpp"
#include "wall.hpp"
#include "MazeLocation.hpp"
#include "ta.hpp"
#include "player.hpp"
#include <random>

/*********************************************************************
** Function: Mazelevel constructors
** Description: Constructs the mazelevel class.
** Parameters: An array of chars, and integers specifing the rows and columns.
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
Mazelevel::Mazelevel(){}

Mazelevel::Mazelevel(char* arr[], int r, int c){
  appeased = false;
    for(int i = 0; i<r ; i++){
      std::vector<Mazelocation*> row;
      for(int j = 0; j<c; j++){
        Mazelocation* p = NULL;
        if(arr[i][j] == '#'){
          p = new Wall;
        }else if(arr[i][j] == '@'){
          Openspace* o = new Openspace(arr[i][j]);
          o->set_has_explorer(true);
          p = o;
          player.set_location(i,j);
        }else{
          p = new Openspace(arr[i][j]);
        }
        row.push_back(p);
      }
      locations.push_back(row);
    }
}

Mazelevel::Mazelevel(const Mazelevel& m){
  //locations = m.locations;
  for(int i =0; i< m.locations.size(); i++){
    std::vector<Mazelocation*> v;
    for(int j=0; j< m.locations.size(); j++){
      v.push_back(m.locations[i][j]->clone());
    }
    locations.push_back(v);
  }
  player = m.player;
  ta1 = m.ta1;
  ta2 = m.ta2;
  appeased = false;
  //std::cout<<"Copy constr called"<<std::endl;
}

void Mazelevel::operator=(const Mazelevel& m){
  locations = m.locations;
  // for(int i =0; i< m.locations.size(); i++){
  //   for(int j=0; j< m.locations.size(); j++){
  //     delete m.locations[i][j];
  //   }
  // }
    player = m.player;
    ta1 = m.ta1;
    ta2 = m.ta2;
    appeased = false;
    std::cout<<"operator overload called"<<std::endl;
}

/*********************************************************************
** Function: getLocations
** Description: Returns a reference to a 2-d array of MazeLocation pointers
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
std::vector<std::vector<Mazelocation*> >& Mazelevel::getLocations(){
  return locations;
}

/*********************************************************************
** Function: getPlayer
** Description: Returns a refernece to the Player class
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
Player& Mazelevel::getPlayer(){
  return player;
}

Mazelevel::~Mazelevel(){
  //std::cout<<"Mazelevel DESTrtr called"<<std::endl;
  for(int i =0; i<locations.size(); i++){
    for(int j = 0; j<locations[i].size(); j++){
      delete locations[i][j];
      locations[i][j] = NULL;
    }
  }
}

/*********************************************************************
** Function: getTa1/2
** Description: Returns a refernece to the TA class
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
TA& Mazelevel::getTa1(){
  return ta1;
}

TA& Mazelevel::getTa2(){
  return ta2;
}

/*********************************************************************
** Function: placeTA
** Description: Combines vectors of mazelocations into a single dimension length nxn vector, then randomlly assigns TA's and programming skills to it.
** Parameters: Integers specifing the rows and columns.
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
void Mazelevel::placeTA( int r, int c){
  std::vector<Mazelocation*> v;
  for(int i =0; i<r; i++){
    for(int j =0; j<c; j++){
        v.push_back(locations[i][j]);//all maze locations in a single dimension vector.
    }
  }
  srand(time(NULL));
   std::random_device rd;
   std::mt19937 eng(rd());
   std::uniform_int_distribution<> distr(0, v.size());
   int count =0;
   // static_cast<Openspace*>(v[18])->set_has_skill(true);
   // static_cast<Openspace*>(v[33])->set_has_skill(true);/////////remember to take these out
   // static_cast<Openspace*>(v[34])->set_has_skill(true);
   while(count < 4){
     int index = distr(eng);
     if(v[index]->is_occupiable()){
       if(count < 2){
         static_cast<Openspace*>(v[index])->set_has_TA(true);
                 // index/cols gives row as quotient and column as remainder
                int row = index/c;
                int col = index % c;
         if(count == 0){
            ta1.set_location(row, col);
         }else{
            ta2.set_location(row, col);
         }
       }else{
         static_cast<Openspace*>(v[index])->set_has_skill(true);
       }
       count++;
     }
   }
}

/*********************************************************************
** Function: moveTA
** Description: calls get_move and verifies that the move is valid, then updates TA's position.
** Parameters: TA&
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
void Mazelevel::moveTA(TA& t){
  bool valid = false;
  char c = t.get_move();
  int newpos;
  int oldpos;
  do{
    c = t.get_move();
    switch(c){
      case 'w':{//up
        oldpos = t.get_row();
        newpos = oldpos;
        newpos--;
        valid = locations[newpos][t.get_col()]->is_occupiable();//need to make sure that moves are within bounds, eg a TA at zero, zero that gets a 'w' char shouldnt segfault.
        //the larger issue is that TAs arent internally updated to their new positions, only the maze knows where they are, whic is why their positions are 0,0.
        break;
      }
      case 's':{//down
        oldpos = t.get_row();
        newpos = oldpos;
        newpos++;
        valid = locations[newpos][t.get_col()]->is_occupiable();
        break;
      }
      case 'a':{//left
        oldpos = t.get_col();
        newpos = oldpos;
        newpos--;
        valid = locations[t.get_row()][newpos]->is_occupiable();
        break;
      }
      case 'd':{//right
        oldpos = t.get_col();
        newpos = oldpos;
        newpos++;
        valid = locations[t.get_row()][newpos]->is_occupiable();
        break;
      }
    }
    // if(!valid){
    //   std::cout<<"Move is invalid"<<std::endl;
    // }
  }while(!valid);
  switch(c){
    case 'w':{//rows
      static_cast<Openspace*>(locations[oldpos][t.get_col()])->set_has_TA(false);
      static_cast<Openspace*>(locations[newpos][t.get_col()])->set_has_TA(true);
      // static_cast<Openspace*>(locations[t.get_row()][oldpos])->set_has_TA(false);
      // static_cast<Openspace*>(locations[t.get_row()][newpos])->set_has_TA(true);
      t.set_location(newpos, t.get_col() );//ta's position is not changing
      //ta's x and y coordinates are being switched every loops
    //  t.set_location(t.get_col(), newpos);
      break;
    }
    case 'a':{//cols
      static_cast<Openspace*>(locations[t.get_row()][oldpos])->set_has_TA(false);
      static_cast<Openspace*>(locations[t.get_row()][newpos])->set_has_TA(true);
      t.set_location(t.get_row(), newpos);
      //t.set_location(newpos, t.get_row());
      break;
    }
    case 's':{//rows
      static_cast<Openspace*>(locations[oldpos][t.get_col()])->set_has_TA(false);
      static_cast<Openspace*>(locations[newpos][t.get_col()])->set_has_TA(true);
      t.set_location(newpos, t.get_col());
      //t.set_location(t.get_col(), newpos);
      break;
    }
    case 'd':{
      static_cast<Openspace*>(locations[t.get_row()][oldpos])->set_has_TA(false);
      static_cast<Openspace*>(locations[t.get_row()][newpos])->set_has_TA(true);
      t.set_location(t.get_row(), newpos);
      //t.set_location(newpos, t.get_row());
      break;
    }
  }
}

/*********************************************************************
** Function: movePlayer
** Description: calls player's get_move, then verifies the move to be valid before updating the pplayers positon. Also keeps track of how long TA's are appeased foe.
** Parameters: boolean specifying whether or not it has been ten turns since the player last demonstrated skills.
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
int Mazelevel::movePlayer(bool b){
    if(b){
      appeased = false;
      std::cout << "tas are no longer appeased" << '\n';
    }
    bool valid = false;
    char c;
    int newpos;
    int oldpos;
    if(player.getNskills() >= 3 ){
      std::string str = "You have learned enough programming skills to demonstrate them to the TAs. Press 'd' to demonstrate, or 'c' to continue.";
      char c = get_input(str, 'd', 'c');
      if(c == 'd'){
        player.loseskills(3);
        appeased = true;
      }
    }
  do{
    c = player.get_move();
    switch(c){
      case 'w':{//up
        oldpos = player.get_row();
        newpos = oldpos;
        newpos--;
        valid = locations[newpos][player.get_col()]->is_occupiable();
        break;
      }
      case 's':{//down
        oldpos = player.get_row();
        newpos = oldpos;
        newpos++;
        valid = locations[newpos][player.get_col()]->is_occupiable();
        break;
      }
      case 'a':{//left
        oldpos = player.get_col();
        newpos = oldpos;
        newpos--;
        valid = locations[player.get_row()][newpos]->is_occupiable();
        break;
      }
      case 'd':{//right
        oldpos = player.get_col();
        newpos = oldpos;
        newpos++;
        valid = locations[player.get_row()][newpos]->is_occupiable();
        break;
      }
    }
    if(!valid){
      std::cout<<"Move is invalid"<<std::endl;
    }
  }while(!valid);
  switch(c){
    case 'w':{//rows
      static_cast<Openspace*>(locations[oldpos][player.get_col()])->set_has_explorer(false);
      static_cast<Openspace*>(locations[newpos][player.get_col()])->set_has_explorer(true);
      player.set_location(newpos, player.get_col() );
      break;
    }
    case 'a':{//cols
      static_cast<Openspace*>(locations[player.get_row()][oldpos])->set_has_explorer(false);
      static_cast<Openspace*>(locations[player.get_row()][newpos])->set_has_explorer(true);
      player.set_location(player.get_row(), newpos);
      break;
    }
    case 's':{//rows
      static_cast<Openspace*>(locations[oldpos][player.get_col()])->set_has_explorer(false);
      static_cast<Openspace*>(locations[newpos][player.get_col()])->set_has_explorer(true);
      player.set_location(newpos, player.get_col());
      break;
    }
    case 'd':{
      static_cast<Openspace*>(locations[player.get_row()][oldpos])->set_has_explorer(false);
      static_cast<Openspace*>(locations[player.get_row()][newpos])->set_has_explorer(true);
      player.set_location(player.get_row(), newpos);
      break;
    }
  }
  if(appeased){
    return 1;
  }else{
    return 0;
  }
}

/*********************************************************************
** Function: win
** Description: checks certain criteria and returns a boolean if the player has met the winning conditions.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
bool Mazelevel::win(){
  if( static_cast<Openspace*>( locations[player.get_row()-1][player.get_col()] )->getInstructor() || static_cast<Openspace*>( locations[player.get_row()+1][player.get_col()] )->getInstructor() || static_cast<Openspace*>( locations[player.get_row()][player.get_col()-1] )->getInstructor() || static_cast<Openspace*>( locations[player.get_row()][player.get_col()+1] )->getInstructor()){
    if( player.getNskills() >= 3){
      return true;
    }else{
      return false;
    }
  }else{
     return false;
  }
}

/*********************************************************************
** Function: get_location
** Description: Not sure how/why to use this, was specified as being required.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
Mazelocation* Mazelevel::get_location(int r, int c){
  return locations[r][c];
}

/*********************************************************************
** Function: display_maze
** Description: Displays the game grid.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
void Mazelevel::display_maze(){
  // This method should use the `get_display_character()
  char c;
  for(int i = 0; i<locations.size(); i++){
    for(int j =0; j<locations[i].size(); j++){
      if(locations[i][j]->is_occupiable()){//not a wall
        if(static_cast<Openspace*>(locations[i][j])->has_explorer()){//not start or end
          c = 'X';
        }else if(static_cast<Openspace*>(locations[i][j])->has_TA()){
          c = 'T';
        }else if( static_cast<Openspace*>(locations[i][j])->get_skill() ){
          c = 'P';
        }else{
          c = locations[i][j]->get_display_character();
        }
      }else{//all walls
        c = locations[i][j]->get_display_character();
      }
      std::cout<<c<<' ';
      }
      std::cout<<'\n';
  }

}

/*********************************************************************
** Function: check
** Description: checks if the player has enough skills to demonstrate, and whether or not TAs are in range.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
void Mazelevel::check(){
  //check squares nsew of player and player's current location for TA's and skills.
  int r = player.get_row();
  int c = player.get_col();
  if( static_cast<Openspace*>(locations[r][c])->get_skill() ){
    static_cast<Openspace*>(locations[r][c])->set_has_skill(false);
    player.addskill();
  }
  if( static_cast<Openspace*>(locations[r][c])->has_TA() || static_cast<Openspace*>(locations[r-1][c])->has_TA() || static_cast<Openspace*>(locations[r+1][c])->has_TA() || static_cast<Openspace*>(locations[r][c-1])->has_TA() || static_cast<Openspace*>(locations[r][c+1])->has_TA() ){
    if( !appeased ){
      player.loseskills(player.getNskills());
      std::cout<<"You got caught by a TA and lost all your programming skills!"<<std::endl;
    }
  }
}

/*********************************************************************
** Function: advance
** Description: Checks to see if the player is on the move up tile, and returns true if this is the case.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
bool Mazelevel::advance(){
  if( static_cast<Openspace*>( locations[player.get_row()][player.get_col()] )->is_end() ){
    return true;
  }else if(static_cast<Openspace*>( locations[player.get_row()-1][player.get_col()] )->getInstructor() || static_cast<Openspace*>( locations[player.get_row()+1][player.get_col()] )->getInstructor() || static_cast<Openspace*>( locations[player.get_row()][player.get_col()-1] )->getInstructor() || static_cast<Openspace*>( locations[player.get_row()][player.get_col()+1] )->getInstructor()){
    return true;
  }else{
    return false;
  }
}

/*********************************************************************
** Function: get_input
** Description: Prompts and validates user input.
** Parameters: String that contains the prompt, chars that are the acceptable responses.
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
char Mazelevel::get_input(std::string prompt, char c1, char c2){
  bool flag = false;
  char in = '0';
  do{
    std::cout<<prompt<<std::endl;
    std::cin>> in;
    if(in != c1 && in != c2){
      std::cout<<"Please enter a valid choice."<<std::endl;
      flag = true;
    }else{
      flag = false;
    }
  }while(flag);
  return in;
}
