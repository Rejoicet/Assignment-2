#include "Gameoflife.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <limits>
#include <cstdlib>                  //to use rand function
#include <ctime>                    //to initialize srand function to time(NULL)

using namespace std;

Originalgrid::Originalgrid ()
{
  n = 0;
  countofx = 1;
}

char Originalgrid::setOriginalgrid (string filename, char mode, int output, char type, int rows, int columns)
{
  if (type == 'R' || type == 'r') {
    r = rows;
    c = columns;
    TotalArea = r*c;
    srand (time(NULL));
    density = rand()/(RAND_MAX+1.0);
    NoofX = density*TotalArea;

    a = r;
    b = c;

    ptrr = new int;
    *ptrr = r;
    ptrc = new int;
    *ptrc = c;

    pdimensions = new char*[a+2];

    for (int i = 0; i < a+2; i++) {
      for (int j = 0; j < b+2; j++) {
        pdimensions[i] = new char[b+2];
      }
    }

    r = 1;
    c = 1;

    for (int i = 0; i < a+2; i++) {
      for (int j = 0; j < b+2; j++) {
        *(*(pdimensions + i) + j) = '-';
      }
    }

    for (int i = 1; i < a+1; i++) {
      for (int j = 1; j < b+1;   j++) {
        if (NoofX != 0) {
          *(*(pdimensions + i) + j) = 'X';
          --NoofX;
        }
      }
    }

  } else if (type == 'F' || type == 'f') {
    Gameoflife.open (filename);

    if (!Gameoflife) {             //Exception if error in opening file
      cout << "Unable to open the file. Please check the following and run the program again -" << endl;
      cout << "1 - File is not open already" << endl;
      cout << "2 - Check some other program is not using it" << endl;
      cout << "3 - File name/path is correct" << endl;
      exit(1);
    }
    
    getline (Gameoflife,s);
    istringstream firstrow (s);
    firstrow >> r;
    getline (Gameoflife,s);
    istringstream secondrow (s);
    secondrow >> c;

    a = r;
    b = c;

    ptrr = new int;
    *ptrr = r;
    ptrc = new int;
    *ptrc = c;

    pdimensions = new char*[a+2];

    for (int i = 0; i < a+2; i++) {
      for (int j = 0; j < b+2; j++) {
        pdimensions[i] = new char[b+2];
      }
    }

    r = 1;
    c = 1;

    for (int i = 0; i < a+2; i++) {
      for (int j = 0; j < b+2; j++) {
        *(*(pdimensions + i) + j) = '-';
      }
    }

    while (Gameoflife >> cell) {
      if (c == b) {
        *(*(pdimensions + r) + c) = cell;
        r++;
        c = 1;
      }
      else {
        *(*(pdimensions + r) + c) = cell;
        c++;
      }
    }

  }

  if (mode == 'M' || mode == 'm') {
    for (int i = 0; i < 1; i++) {
      for (int j = 1; j < b+2 ; j++) {
        *(*(pdimensions + i) + j) = *(*(pdimensions + i+1) + j);
      }
    }
    for (int i = a+1; i < a+2 ; i++) {
      for (int j = 1; j < b+2; j++) {
        *(*(pdimensions + i) + j) = *(*(pdimensions + i-1) + j);
      }
    }
    for (int i = 1; i < a+2; i++) {
      for (int j = 0; j < 1; j++) {
        *(*(pdimensions + i) + j) = *(*(pdimensions + i) + j+1);
      }
    }
    for (int i = 1; i < a+2; i++) {
      for (int j = b+1; j < b+2; j++) {
        *(*(pdimensions + i) + j) = *(*(pdimensions + i) + j-1);
      }
    }
    *(*(pdimensions + 0) + 0) = *(*(pdimensions + 1) + 1);
    *(*(pdimensions + 0) + b+1) = *(*(pdimensions + 1) + b);
    *(*(pdimensions + a+1) + 0) = *(*(pdimensions + a) + 1);
    *(*(pdimensions + a+1) + b+1) = *(*(pdimensions + a) + b);
  }


  if (output == 3) {
    freopen ("Rejoice.out", "w", stdout);
  };

  cout << "Generation number: 0" << endl;

  for (int i = 1; i < a+1; i++) {
    for (int j = 1; j < b+1; j++) {
      cout << *(*(pdimensions + i) + j);
    }
    cout << endl;
  }

  int xcount = 0;

  for (int i = 1; i < *ptrr+1; i++) {
    for (int j = 1; j < *ptrc+1; j++) {
      if (*(*(pdimensions + i) + j) == 'X') {
        ++xcount;
      }
    }
  }

  if (xcount == 0) {
    cout << "The current generation is nice and stable. No more generations possible. Tada!" << endl;
    exit(1);
  }

}

char Originalgrid::copyOriginalgrid ()
{
  copypdimensions = new char*[*ptrr];

  for (int i = 0; i < *ptrr+2; i++) {
    for (int j = 0; j < *ptrc+2; j++) {
      copypdimensions[i] = new char [*ptrc+2];
    }
  }

  count = new int*[*ptrr];

  for (int i = 0; i < *ptrr+2; i++) {
    for (int j = 0; j < *ptrc+2; j++) {
      count[i] = new int [*ptrc+2];
    }
  }

  for (int i = 0; i < *ptrr+2; i++) {         //copying the current generation
    for (int j = 0; j < *ptrc+2; j++) {
      *(*(copypdimensions + i) + j) = *(*(pdimensions + i) + j);
    }
  }

}

char Originalgrid::updateOriginalgrid (char mode, int output)
{

  while (countofx != 0) {

    if (output == 2) {
      cout << "Press ENTER to contine..." << endl;
      cin.ignore (numeric_limits <streamsize> :: max(), '\n');
    } else if (output == 1) {
      chrono::seconds dura (3);
      this_thread::sleep_for (dura);
    }

    int check = 0;

    for (int i = 1; i < *ptrr+1; i++) {
      for (int j = 1; j < *ptrc+1; j++) {
        ncount = 0;
        for (int k = i-1; k < i+2; k++) {
          for (int l = j-1; l < j+2; l++) {
            if (*(*(copypdimensions + k) + l) == 'X') {
              ++ncount;
            }
          }
        }
        if (*(*(copypdimensions + i) + j) == 'X') {
          --ncount;
        }
        *(*(count + i) + j) = ncount;
      }
    }

    for (int i = 1; i < *ptrr+1; i++) {
      for (int j = 1; j < *ptrc+1; j++) {
        if (*(*(count + i) +j) == 3) {
          if (*(*(pdimensions + i) + j) == '-') {
            *(*(pdimensions + i) + j) = 'X';
          }
        } else if (*(*(count + i) + j) != 2 && *(*(count + i) + j) != 3) {
          if (*(*(pdimensions + i) + j) == 'X') {
            *(*(pdimensions + i) + j) = '-';
          }
        } else continue;
      }
    }

    for (int i = 1; i < *ptrr+1; i++) {
      for (int j = 1; j < *ptrc+1; j++) {
        if (*(*(copypdimensions + i) + j) != *(*(pdimensions + i) +j)) {
          ++check;
        }
      }
    }

    if (check == 0) {
      cout << "The current generation is nice and stable. No more generations possible. Tada!" << endl;
      exit(1);
    }

    ++n;
    cout << "Generation number: " << n << endl;

    for (int i = 1; i < *ptrr+1; i++) {
      for (int j = 1; j < *ptrc+1; j++) {
        cout << *(*(pdimensions + i) + j);
      }
      cout << endl;
    }

    if (mode == 'M' || mode == 'm') {
      for (int i = 0; i < 1; i++) {
        for (int j = 1; j < b+2 ; j++) {
          *(*(pdimensions + i) + j) = *(*(pdimensions + i+1) + j);
        }
      }
      for (int i = a+1; i < a+2 ; i++) {
        for (int j = 1; j < b+2; j++) {
          *(*(pdimensions + i) + j) = *(*(pdimensions + i-1) + j);
        }
      }
      for (int i = 1; i < a+2; i++) {
        for (int j = 0; j < 1; j++) {
          *(*(pdimensions + i) + j) = *(*(pdimensions + i) + j+1);
        }
      }
      for (int i = 1; i < a+2; i++) {
        for (int j = b+1; j < b+2; j++) {
          *(*(pdimensions + i) + j) = *(*(pdimensions + i) + j-1);
        }
      }
      *(*(pdimensions + 0) + 0) = *(*(pdimensions + 1) + 1);
      *(*(pdimensions + 0) + b+1) = *(*(pdimensions + 1) + b);
      *(*(pdimensions + a+1) + 0) = *(*(pdimensions + a) + 1);
      *(*(pdimensions + a+1) + b+1) = *(*(pdimensions + a) + b);
    }

    for (int i = 0; i < *ptrr+2; i++) {         //copying the current generation
      for (int j = 0; j < *ptrc+2; j++) {
        *(*(copypdimensions + i) + j) = *(*(pdimensions + i) + j);
      }
    }

    xcount = 0;

    for (int i = 1; i < *ptrr+1; i++) {
      for (int j = 1; j < *ptrc+1; j++) {
        if (*(*(pdimensions + i) + j) == 'X') {
          ++xcount;
        }
      }
    }

    countofx = xcount;

  }

  fclose (stdout);

  if (countofx == 0) {
    cout << "The current generation is nice and stable. No more generations possible. Tada!" << endl;
    exit(1);
  }

}
