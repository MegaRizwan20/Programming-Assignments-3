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
  // The stream we are taking in
  std::ifstream READ;
  // The stream we are writing to
  std::ofstream WRITE;
  // The tree we are making
  HCTree theTree;
  //std::vector<int> treeVec(256, 0);
  // The vector we are storing everything into
  std::vector<unsigned int> treeVec(256, 0);
  // Integer used to iterate through vector
  unsigned int k = 0;
  // Used for going through vector
  unsigned int l = 0;
  // Storing the value of the character
  unsigned int store = 0;
  // Figuring out how many characters there are in file
  unsigned int addStores = 0;
  // Character we are reading in
  unsigned char y;
  //unsigned char nxtChar;
  //char z;

  READ.open(argv[1]);
  //BitInputStream* READ2 = new BitInputStream(READ);
  //READ2->fill();
  for (k = 0; k < treeVec.size(); k++)
  {
    READ>>store;
    treeVec[k] = store;
    addStores = addStores + store;
    //cout << "THE FIRST FOR " << endl;
  }

  //BitInputStream* READ2 = new BitInputStream(READ);
  /*int nextByte;
  while ((nextByte = READ.get()) != EOF)
  {
    nxtChar = (unsigned char)nextByte;
    cout << nextByte << endl;
    cout << nxtChar << endl;
  }*/



  //cout << " AFTER THE FOR LOOP" << endl;
  //BitInputStream* READ2 = new BitInputStream(READ);
  // Build the tree 
  theTree.build(treeVec);
  BitInputStream* READ2 = new BitInputStream(READ);
  READ2->fill();

  //cout << " SO MUCH CODE" << endl;
  WRITE.open(argv[2]);

  //BitInputStream* READ2 = new BitInputStream(READ);
  //READ2->fill();
  //cout << addStores << endl;
  // Decoding all the necessary characters
  for (k = 0; k < addStores; k++)
  {
    //y = theTree.decode(READ);
    y = theTree.decode(*READ2);
    //cout << y << endl;
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
