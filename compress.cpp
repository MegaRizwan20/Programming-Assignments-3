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
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
  ifstream READ;
  ofstream WRITE;
  //BitOutputStream WRITE;
  // Pass this in after you open up the file.
  //BitOutputStream* WRITE2 = new BitOutputStream(WRITE);
  HCTree theTree;
  //std::vector<int> treeVec(256, 0);
  std::vector<unsigned int> treeVec(256, 0);
  //treeVec = vector<HCNode*>(256, (HCNode*) 0);
  unsigned int k = 0;
  unsigned char y;
  unsigned int x = 0;
  string theString;
  //char z;

  READ.open(argv[1]);

  // Read through the file and increment when I fin the character
  //while (READ.get(y) != NULL)
  //READ.get();
  while (1)
  {
    //std::getline(READ, theString);
    //x = stoi(theString);
    y = READ.get();
    //treeVec[(int) y]++;
    treeVec[y]++;
    //treeVec[x]++;
    //cout << "TREEVEC" << endl;
    //treeVec.push();
    if (!READ.good())
    {
      break;
    }
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
  BitOutputStream* WRITE2 = new BitOutputStream(WRITE);

  //cout << "AFTER JK " << endl;
  //while (READ.get(z) != NULL)
  //while (READ.get(y) != NULL)
  // To Throw a newline character
  //READ.get();
  while (1)
  {
    //std::getline(READ, theString);
    y = READ.get();
    
    //cout << "START ENCODE " << endl;
    //theTree.encode((byte)y, WRITE);
    theTree.encode((byte)y, *WRITE2);
    //cout << "THE ENCODE " << endl;
    if (!READ.good())
    {
      break;
    }
  }
  WRITE2->flush();
  READ.close();
  WRITE.close();
  delete WRITE2;
  /*if('a'<'b'){
    cout << "hello" << endl;
	}
*/
  return 1;
}
