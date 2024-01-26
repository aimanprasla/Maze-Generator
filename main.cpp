#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <vector> 
#include <ctime> 
#include "Maze.h"
using namespace std; 



int main()
{
  int seed;
  string type;
  cout << "Enter the seed: ";
  cin >> seed; 

  srand(seed);
  
  Maze maze;
  maze.prim();
  maze.printGrid();
  maze.bfs();

  return 0; 
}