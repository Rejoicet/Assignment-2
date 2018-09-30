#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Corners;

class Originalgrid {
public:
  ifstream Gameoflife;
  string s;
  int r, c, a, b, abc, ncount, xcount, countofx, n;
  int *ptrr, *ptrc;
  char cell, value;
  char ** pdimensions;
  char ** copypdimensions;
  int ** count;


  Originalgrid ();
  char setOriginalgrid (string filename, char mode, int output);
  char copyOriginalgrid ();
  char updateOriginalgrid (char mode, int output);
  void updateCorners(Corners& corner);

};
