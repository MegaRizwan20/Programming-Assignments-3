/*
 * Author: Rizwan Khan
 * CSE100 Login: cs100sgv
 * PID: A12236946
 * Email: rikhan@ucsd.edu
 */

#include "HCTree.h"
#include <ctype.h>
#include <iostream>

using namespace std;

int main (int argc, char* argv[])
{
  std::ifstream READ;
  std::ofstream WRITE;
  HCTree theTree;
  std::vector<int> treeVec(256, 0);
  int k = 0;
  int l = 0;
  int store = 0;
  int addStores = 0;
  char y;
  //char z;

  READ.open(argv[1]);
  for (k = 0; k < treeVec.size(); k++)
  {
    READ>>store;
    treeVec[k] = store;
    addStores = addStores + store;
    //cout << "THE FIRST FOR " << endl;
  }
  //cout << " AFTER THE FOR LOOP" << endl;
  theTree.build(treeVec);
  //cout << " SO MUCH CODE" << endl;
  WRITE.open(argv[2]);

  for (k = 0; k < addStores; k++)
  {
    y = theTree.decode(READ);
    if (y == -1)
    {
      break;
    }
    WRITE << y;
  }
  READ.close();
  WRITE.close();
  return 1;
}
