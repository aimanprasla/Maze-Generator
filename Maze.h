#pragma once
#include <iostream>
#include <stack>
#include <time.h>
#include "Queue.h"
#include <vector>
#include <stdlib.h> 
using namespace std; 


const int SIZE = 5; 

struct Cell
{
  int row;
  int col;
  bool visit = false; 
};
struct Edge
{
  int toRow;
  int toCol;
};
struct Wall
{
  bool north;
  bool south;
  bool east;
  bool west;
};

class Maze{
public: 
  Maze();
  ~Maze();
  void prim();
  void printGrid();
  void bfs();
  bool markPath(int row, int col);
  void addToVector(vector<Cell>& vector, int, int);
  

private:
  //0 means unused 1 means in border queue, 2 means used and chosen as a path
  //bfs 2 means unvisited, 3 means visited
  int** arr;
  Wall** walls;
  int size;
  int** distances;
  bool** path;
  //int** squares;
  //bool safeBound();
  //vector<vector<Wall>> wall;
  //vector<pair<int, int>> location = {{0,1}, {0,-1}, {1,0}, {0,1}};
  //int num_walls_visited;
}; 

Maze::Maze()
{
  size = SIZE;
  //squares = new int*[size * size]; 
  arr = new int*[size];
  walls = new Wall*[size];
  distances = new int*[size];
  path = new bool*[size];
  for(int a = 0; a < size; a++)
    {
      arr[a] = new int[size];
      walls[a] = new Wall[size];
      distances[a] = new int[size];
      path[a] = new bool[size];
    }
  for(int a = 0; a < size; a++)
    {
      for(int b = 0; b < size; b++)
        {
          Wall temp;
          temp.north = false;
          temp.south = false;
          temp.east = false;
          temp.west = false;
          walls[a][b] = temp;
        }
    }
}
Maze::~Maze()
{
  for(int a = 0; a < size; a++)
    {
      delete[] arr[a];
      delete[] walls[a];
      delete[] distances[a];
      delete[] path[a];
    }
  delete[] arr;
  delete[] walls;
  delete[] distances;
  delete[] path;
}
void Maze::printGrid()
{
  cout << "+";
  for(int b = 0; b < size; b++)
    {
      cout << "-+";   
    }
  cout << endl;
  for(int a = 0; a < size; a++)
    {
      cout << "|";
      for(int b = 0; b < size; b++)
        {
          if(walls[a][b].east == false)
            cout << "  ";
          else
            cout << " |";
        }
      cout << endl;
      cout << "+";
      for(int b = 0; b < size; b++)
        {
          if(walls[a][b].south == false)
            cout << " +";
          else
            cout << "-+";
        }
      cout << endl;
    }
}

void Maze::prim()
{
  vector<Cell> vector;
  Edge temp;
  int random = 0;
  int row, col;
  row = rand() % size;
  col = rand() % size;
  arr[row][col] = 2;
  cout << "Chose: " << row << " " << col << endl;
  addToVector(vector, row, col);
  
  while(vector.size() != 0)
    {
      random = rand() % vector.size();
      temp.toCol = vector[random].col;
      temp.toRow = vector[random].row;
      cout << "Chose: " << temp.toRow << " " << temp.toCol << endl;
      
      if(temp.toRow+1 < size && arr[temp.toRow+1][temp.toCol] == 2)
      {
        walls[temp.toRow+1][temp.toCol].north = true;
        walls[temp.toRow][temp.toCol].south = true;
        cout << "South: True" << endl;
      }
      if(temp.toRow-1 >= 0 && arr[temp.toRow-1][temp.toCol] == 2)
      {
        walls[temp.toRow-1][temp.toCol].south = true;
        walls[temp.toRow][temp.toCol].north = true;
        cout << "North: True" << endl;
      }
      if(temp.toCol+1 < size && arr[temp.toRow][temp.toCol+1] == 2)
      {
        walls[temp.toRow][temp.toCol].east = true;
        walls[temp.toRow][temp.toCol+1].west = true;
        cout << "East: True" << endl;
      }
      if(temp.toCol-1 >= 0 && arr[temp.toRow][temp.toCol-1] == 2)
      {
        walls[temp.toRow][temp.toCol].west = true;
        walls[temp.toRow][temp.toCol-1].east = true;
        cout << "West: True" << endl;
      }
      
      int countWalls = 0;
      if(walls[temp.toRow][temp.toCol].north)
        countWalls++;
      if(walls[temp.toRow][temp.toCol].south)
        countWalls++;
      if(walls[temp.toRow][temp.toCol].east)
        countWalls++;
      if(walls[temp.toRow][temp.toCol].west)
        countWalls++;
      if(countWalls > 1)
      {
        cout << "More than one border paths: " << countWalls << endl;
        while(countWalls != 1)
          {
            int rnd = rand() % 4;
            if(rnd == 0)
            {
              if(walls[temp.toRow][temp.toCol].south == true)
              {
                walls[temp.toRow][temp.toCol].south = false;
                countWalls--;
                cout << "Removed South, Paths left: " << countWalls << endl;
              }
            }
            else if(rnd == 1)
            {
              if(walls[temp.toRow][temp.toCol].east == true)
              {
                walls[temp.toRow][temp.toCol].east = false;
                countWalls--;
                cout << "Removed East, Paths left: " << countWalls << endl;
              }
            }
            else if(rnd == 2)
            {
              if(walls[temp.toRow][temp.toCol].west == true)
              {
                walls[temp.toRow][temp.toCol].west = false;
                countWalls--;
                cout << "Removed West, Paths left: " << countWalls << endl;
              }
            }
            else if(rnd == 3)
            {
              if(walls[temp.toRow][temp.toCol].north == true)
              {
                walls[temp.toRow][temp.toCol].north = false;
                countWalls--;
                cout << "Removed North, Paths left: " << countWalls << endl;
              }
            }
          }
      }
      arr[temp.toRow][temp.toCol] = 2;
      
      addToVector(vector, temp.toRow, temp.toCol);
      vector.erase(vector.begin() + random);
    }
  
}
void Maze::addToVector(vector<Cell>& vector, int row, int col)
{
  Cell temp;
  temp.row = row;
  temp.col = col;

  //north
  temp.row--;
  if(temp.row >= 0)
  {
    if(arr[temp.row][temp.col] == 0)
    {
      vector.push_back(temp);
      cout << "Added to border queue: " << temp.row << " " << temp.col << endl;
      arr[temp.row][temp.col] = 1;
    }
  }
  //south
  temp.row+=2;
  if(temp.row <= size-1)
  {
    if(arr[temp.row][temp.col] == 0)
    {
      vector.push_back(temp);
      cout << "Added to border queue: " << temp.row << " " << temp.col << endl;
      arr[temp.row][temp.col] = 1;
    }
  }

  temp.row--;
  
  //west
  temp.col--;
  if(temp.col >= 0)
  {
    if(arr[temp.row][temp.col] == 0)
    {
      vector.push_back(temp);
      cout << "Added to border queue: " << temp.row << " " << temp.col << endl;
      arr[temp.row][temp.col] = 1;
    }
  }
  //east
  temp.col+=2;
  if(temp.col <= size-1)
  {
    if(arr[temp.row][temp.col] == 0)
    {
      vector.push_back(temp);
      cout << "Added to border queue: " << temp.row << " " << temp.col << endl;
      arr[temp.row][temp.col] = 1;
    }
  }
}
void Maze::bfs()
{
  Queue q;
  for(int a = 0; a < size; a++)
    {
      for(int b = 0; b < size; b++)
        {
          distances[a][b] = 100000;
        }
    }
  distances[0][0] = 0;
  int row, col;
  arr[0][0] = 3;
  q.enqueue(0,0);
  while(!q.isEmpty())
    {
      row = q.top()->row;
      col = q.top()->col;
      //cout << "Chose: " << row << " " << col << endl;
      q.dequeue();
      if(row+1 <= size-1 && arr[row+1][col] == 2 && walls[row][col].south)
      {
        q.enqueue(row+1, col);
        arr[row+1][col] = 3;
        distances[row+1][col] = distances[row][col] + 1;
        //cout << "Added: " << row+1 << " " << col << " Weight: " << distances[row+1][col] << endl;
      }
      if(row-1 >= 0 && arr[row-1][col] == 2 && walls[row][col].north)
      {
        q.enqueue(row-1, col);
        arr[row-1][col] = 3;
        distances[row-1][col] = distances[row][col] + 1;
        //cout << "Added: " << row-1 << " " << col << " Weight: " << distances[row-1][col] << endl;
      }
      if(col+1 <= size-1 && arr[row][col+1] == 2 && walls[row][col].east)
      {
        q.enqueue(row, col+1);
        arr[row][col+1] = 3;
        distances[row][col+1] = distances[row][col] + 1;
        //cout << "Added: " << row << " " << col+1 << " Weight: " << distances[row][col+1] << endl;
      }
      if(col-1 >= 0 && arr[row][col-1] == 2 && walls[row][col].west)
      {
        q.enqueue(row, col-1);
        arr[row][col-1] = 3;
        distances[row][col-1] = distances[row][col] + 1;
        //cout << "Added: " << row << " " << col-1 << " Weight: " << distances[row][col-1] << endl;
      }
    }
  double percentage;
  percentage = (distances[size-1][size-1] / static_cast<double>(size*size)) * 100;
  cout << "Count: " << distances[size-1][size-1] << " Percentage: " << percentage << endl;

  /*markPath(0, 0);
  for(int a = 0; a < size; a++)
    {
      for(int b = 0; b < size; b++)
        {
          cout << distances[a][b] << " ";
        }
      cout << endl;
    }
  for(int a = 0; a < size; a++)
    {
      for(int b = 0; b < size; b++)
        {
          cout << path[a][b] << " ";
        }
      cout << endl;
    }*/
}
bool Maze::markPath(int row, int col)
{
  if(row == size-1 && col == size-1)
  {
    path[row][col] = true;
    return true;
  }
  path[row][col] = true;
  if(row+1 <= size-1 && distances[row+1][col] == (distances[row][col] + 1))
  {
    if(!(markPath(row+1, col)))
      path[row][col] = false;
  }
  if(row-1 >= 0 && distances[row-1][col] == (distances[row][col] + 1))
  {
    if(!(markPath(row-1, col)))
      path[row][col] = false;
  }
  if(col+1 <= size-1 && distances[row][col+1] == (distances[row][col] + 1))
  {
    if(!(markPath(row, col+1)))
      path[row][col] = false;
  }
  if(col-1 >= 0 && distances[row][col-1] == (distances[row][col] + 1))
  {
    if(!(markPath(row, col-1)))
      path[row][col] = false;
  }
  return false;
}