#include <iostream>
#include <fstream>              //to input and output with files
#include <string>
#include <sstream>

using namespace std;

class Originalgrid {
public:
  ifstream Gameoflife;

  string s;

  int r, c, a, b, abc, ncount, xcount, countofx, n, NoofX, TotalArea;
  int *ptrr, *ptrc;
  int ** count;

  char cell, value;
  char ** pdimensions;
  char ** copypdimensions;

  float density;

  Originalgrid ();
  char setOriginalgrid (string filename, char mode, int output, char type, int rows, int columns);
  char copyOriginalgrid ();
  char computeOriginalgrid (char mode, int output);

};
