#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include "Gameoflife.h"
using namespace std;

string nameoffile;

char mod, typ;

int out, row, column;


int main () {

  cout << "Please enter the alphabet against the input you desire to run: " << endl;
  cout << "R - I want to give dimensions and run it randomly" << endl;
  cout << "F - I want to enter the file name situated in the location" << endl;
  cin >> typ;

  if (typ == 'R' || typ == 'r') {
    cout << "Please enter the number of rows" << endl;
    cin >> row;
    cout << "Please enter the number of columns" << endl;
    cin >> column;
  } else if (typ == 'F' || typ == 'f') {
    cout << "Please enter the exact name of the file with the extension: " << endl;
    cin >> nameoffile;
  }

  cout << "Enter the alphabet displayed against the mode you wish to run: " << endl;
  cout << "C - I want to run in Classic mode" << endl;
  cout << "M - I want to run in Mirror mode" << endl;
  cin >> mod;

  cout << "Enter the number of your choice from the following: " << endl;
  cout << "1 - I want a brief pause between generations" << endl;
  cout << "2 - I want to press enter before each generation" << endl;
  cout << "3 - I want the output to be sent to another file" << endl;
  cin >> out;

  Originalgrid dimension1;
  dimension1.setOriginalgrid(nameoffile, mod, out, typ, row, column);
  dimension1.copyOriginalgrid();
  dimension1.updateOriginalgrid(mod, out);

  return 0;

}
