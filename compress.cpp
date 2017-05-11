/*
 * Author: Rizwan Khan
 * CSE100 Login: cs100sgv
 * PID: A12236946
 * Email: rikhan@ucsd.edu
 */

//#include <stdlib>
#include "HCTree.h"
#include <ctype.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
  ifstream READ;
  ofstream WRITE;
  HCTree theTree;
  std::vector<int> treeVec(256, 0);
  //treeVec = vector<HCNode*>(256, (HCNode*) 0);
  int k = 0;
  char y;
  //char z;

  READ.open(argv[1]);

  // Read through the file and increment when I fin the character
  while (READ.get(y) != NULL)
  {
    treeVec[(int) y]++;
    //cout << "TREEVEC" << endl;
    //treeVec.push();
  }
  READ.close();
  theTree.build(treeVec);

  WRITE.open(argv[2]);
  for (k = 0; k < treeVec.size(); k++)
  {
    WRITE << treeVec[k] << endl;
    //cout << "HELLO " << endl;
  }
  //cout << "JK " << endl;
  READ.open(argv[1]);

  //cout << "AFTER JK " << endl;
  //while (READ.get(z) != NULL)
  while (READ.get(y) != NULL)
  {
    //cout << "START ENCODE " << endl;
    theTree.encode((byte)y, WRITE);
    //cout << "THE ENCODE " << endl;
  }
  READ.close();
  WRITE.close();

  return 1;
}
