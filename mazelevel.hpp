#ifndef _mazelevel
#define _mazelevel
#include <iostream>
#include <vector>
#include "MazeLocation.hpp"
#include "wall.hpp"
#include "OpenSpace.hpp"
#include "ta.hpp"
#include "player.hpp"

class Mazelevel{
    std::vector<std::vector<Mazelocation*> > locations;
    Player player;
    TA ta1, ta2;
    bool appeased;
  public:
    Mazelevel(char* arr[], int, int);
    Mazelevel();
    ~Mazelevel();
    Mazelevel(const Mazelevel& m);
    void operator=(const Mazelevel& m);
    bool advance();
    bool win();
    void check();
    TA& getTa1();
    TA& getTa2();
    Player& getPlayer();
    std::vector<std::vector<Mazelocation*> >& getLocations();

    void placeTA(int, int);
    int movePlayer(bool);
    void moveTA(TA& t);
    Mazelocation* get_location(int, int);
    void display_maze();
    char get_input(std::string, char, char);
};



#endif
