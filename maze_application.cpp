#include <iostream>
#include <fstream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <fstream>        //ifstream
#include "mazelevel.hpp"
#include "maze_data.hpp"
#include "game.hpp"

int main(int argc, char** argv){
  if( argc != 2){
    std::cout<<"Please specify the name of the file on the command line"<<std::endl;
  }
  std::ifstream infile(argv[1]);                //Takes in file name from command line and throws error if it can't be opened.
  if (infile.fail()){
    std::cout<<"Failure to open file."<<'\n';
    exit(EXIT_FAILURE);
  }

  int nlevels, rows, cols;
  infile>>nlevels>>rows>>cols;
  Game g(infile, nlevels, rows, cols);
  //std::vector<Mazelevel*> levels = g.getlevels();
  bool win = false;
  int nlevel = 0;
  std::vector<Mazelevel*> levels = g.getlevels();
do{

      Mazelevel m = *levels[nlevel];
      m.placeTA(rows, cols);
      TA ta1 = m.getTa1();
      TA ta2 = m.getTa2();
      m.display_maze();
      int count = 0;
      bool tenturns = false;
      while( ! m.advance() ){
          m.moveTA(ta1);
          m.moveTA(ta2);
          count += m.movePlayer(tenturns);
          if(count == 10){
            count = 0;
            tenturns = true;
          }else{
            tenturns = false;
          }
          m.check();
          m.display_maze();
          win = m.win();
       }
      nlevel++;
      if(nlevel == 3 && !win){
        nlevel = 0;
        std::cout<<"Your skills leave much to be desired. Try again"<<std::endl;
      }
  }while(!win);
  std::cout<<"Congratulations, you have escaped from CS162!"<<std::endl;
return 0;
}
