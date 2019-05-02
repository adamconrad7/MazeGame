Lab Exercise #9
===============

This is the repo for CS 162's Lab #9.  You will commit your source code files into this repository for the TAs to check off.  The description of the lab exercise can be found here:

https://docs.google.com/document/d/17xfN5N1SQbQn5hCUHSA8JvwaEQG98yN8n2VI292MQgU/edit?usp=sharing

In this lab, you’ll implement a maze and a random maze exploration algorithm.

## Step 1: Clone the git repository for this lab

We’re going to use git and GitHub Classroom again for this lab.  Just like you did for the previous lab exercises, use git clone to download your repository onto your development machine using the clone URL from your repo on GitHub:
```
git clone REPO_URL
```

## Step 2: Check out `maze_data.hpp`

The file `maze_data.hpp` contains some data specifying a maze.  There are two constant values `MAZE_HEIGHT` and `MAZE_WIDTH` that specify, respectively, the height and width of the maze, in characters.  Then, `MAZE_DATA` is a 2D array of characters representing the maze itself.  There are 4 different characters used:
  * `'#'` – this represents a wall in the maze
  * `' '` (space) – this represents an open space in the maze
  * `'@'` – this represents the start of the maze
  * `'^'` – this represents the end of the maze

In this lab, you’re going to write a classes to represent this maze and an algorithm to explore it randomly, displaying the location of your random explorer in the maze after each step it takes.

## Step 3: Implement classes to represent locations in your maze

You should write one **abstract** class called `MazeLocation` to represent a generic location in the maze.  It should have the following public methods:
  * `bool is_occupiable()` – this will indicate whether this location can be occupied by your maze explorer
  * `char get_display_character()` – this will return the character that should be displayed to represent this location in the maze

After writing the `MazeLocation` class, you should write two classes that derive from it: `Wall` and `OpenSpace`.

The `Wall` class should represent a wall in the maze.  A wall is never occupiable, and its display character is always `'#'`.

The `OpenSpace` class should represent an open space in your maze.  An open space is always occupiable, but its display character might change depending on whether your explorer is in the space or whether it contains the start or end of the maze.  To help with this, you should implement these additional methods for this class:
  * `void set_has_explorer(bool)` and `bool has_explorer()` – use these functions to set and return a boolean class member that lets you know whether your explorer is in this space
  * `void set_is_start(bool)` and `bool is_start()` – use these functions to set and return a boolean class member that lets you know whether this space is the start of the maze
  * `void set_is_end(bool)` and `bool is_end()` – use these functions to set and return a boolean class member that lets you know whether this space is the end of the maze

Implement each of these classes in a separate set of `.hpp` and `.cpp` files.  When you’re done, add and commit your files to your git repo, and push them to your repo on GitHub.

## Step 4: Write a `Maze` class to represent your maze

Now, you should write a `Maze` class to tie together your location classes above to represent a whole maze (note that because the maze in this lab only has one level, the `Maze` class here will actually correspond to the `MazeLevel` class in your final project).  Here are some things you should implement in your `Maze` class:

  * Your class should have a 2D vector of `MazeLocation` pointers to allow you to use polymorphism to represent your maze as a grid of `Wall` and `OpenSpace` objects:
    ```
    std::vector<std::vector<MazeLocation*> > locations;
    ```

  * Your class should have a constructor that takes the following arguments: a 2D array of characters representing the maze (like `MAZE_DATA` from `maze_data.hpp`), an integer representing the maze’s height, and an integer representing the maze’s width.  In this constructor, you should allocate your grid of locations and then loop through the maze data and allocate new `Wall` and `OpenSpace` objects to fill the grid, e.g.:
    ```
    this->locations[i][j] = new Wall()
    ```
    or
    ```
    this->locations[i][j] = new OpenSpace();
    ```

  * You should write a destructor that frees the space you allocate in the constructor.

  * You should write a method to return the `MazeLocation` at a specified row and column of the grid:
    ```
    MazeLocation* get_location(int, int);
    ```

  * You should write a method to display the maze in the console:
    ```
    void display_maze();
    ```
    This method should use the `get_display_character()` method to get the character to display for each of the individual locations.

Implement this class in a separate set of `.hpp` and `.cpp` files.  When you’re done, add and commit your new files to your git repo, and push them to your repo on GitHub.

## Step 5: Write an application that creates and displays a maze

Now, write a small application that creates an object of your `Maze` class using the data in `maze_data.hpp`.  Then, use the `display_maze()` method to display your maze.  When you’re done, add and commit your application code to your git repo, and push it to your repo on GitHub.

## Step 6: Write an Explorer class that explores your maze

Now, write an `Explorer` class that will randomly explore your maze.  Your class should have data members to hold the row and column of your explorer’s location in the maze.  In addition, you should implement these methods:
  * `char get_move()` – this method should randomly select a direction in which to move (e.g. using the `rand()` function) and return a character code (e.g. `'W'`, `'A'`, `'S'`, `'D'`) to indicate the direction chosen.
  * `void set_location(int, int)` – this method should set the current location of your explorer.
  * `int get_row()` and `int get_col()` – these methods should return the row and column, respectively, of your explorer’s current location.

Once your `Explorer` class is written, use it in your application to explore your maze object.  Your exploration will probably happen within a small loop that does these things:
  * Calls your explorer’s `get_move()` method to get a move direction.
  * Uses a combination of the selected move direction and your explorer’s current location to figure out the row and column of the space to which the explorer is trying to move.
  * Uses your `Maze` class’s `get_location()` method to get the `MazeLocation` object representing the space to which the explorer is trying to move.
  * Calls the `is_occupiable()` method on that `MazeLocation` object to see if the explorer can actually move there.
  * Calls the explorer’s `set_location()` method to update its location if the space to which it’s trying to move is, in fact, occupiable.
  * Calls the `is_end()` method on the `MazeLocation` object to see if the explorer has reached the end of the maze.

If it’s helpful, feel free to use the [`sleep_for()`](http://www.cplusplus.com/reference/thread/this_thread/sleep_for/) function to implement a brief delay at each iteration of the main loop, so you can see the `Explorer` move around the maze.  Note that `sleep_for()` is only available in C++11 or later.  You can use the following function if you don't want to use C++11 (e.g. call `sleep(0.01)` to have a 10 ms delay):

```
#include <ctime>
void sleep (float sec) {
  clock_t t0 = clock(), t1 = t0;
  while (t1 - t0 < CLOCKS_PER_SEC * sec) {
    t1 = clock();
  }
}
```

Once everything is working, add your new files and commit your changes to your git repo, and push everything to GitHub.

## Grading Criteria

That’s it!  After you’re done with your lab, make sure you get it checked off by your TA so that you get points for it.  If you don’t get your work checked off, you’ll receive a zero for the lab, and we won’t be able to change your grade, since we’ll have no way to know whether or not you were at the lab.

This lab is worth 10 points total.  Here’s the breakdown:
  * 3 points: `MazeLocation`, `Wall`, and `OpenSpace` classes
  * 4 points: `Maze` class and application displaying the maze
  * 3 points: `Explorer` class
