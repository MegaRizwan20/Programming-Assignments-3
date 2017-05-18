/*
 * Author: Rizwan Khan
 * CSE100 Login: cs100sgv
 * PID: A12236946
 * Email: rikhan@ucsd.edu
 */

#include "HCTree.h"
#include <ctype.h>
#include <iostream>
#include <string>

using namespace std;

/**
 * Function: Main
 * Parameters: argc, argv[]
 * Purpose: Reads in the bits in the tree to decode the bits and recreate
 * the file that was compressed previously
 * */
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
  // The string that we take into the code
  string theString;

  // open the file that we are reading
  READ.open(argv[1]);
  // Loop through the vector to put in the frequencies
  for (k = 0; k < treeVec.size(); k++)
  {
    // Getting the characters
    std::getline(READ, theString);
    //READ>>store;
    //treeVec[k] = store;
    // Storing the frequency into a vector
    treeVec[k] = (unsigned int)stoi(theString,nullptr, 0);
    //addStores = addStores + store;
    // Counting the number of characters in the file
    addStores = addStores + treeVec[k];
  }

  // Build the tree so we can decode it
  theTree.build(treeVec);
  // The BitInputStream that we need to decode the tree
  BitInputStream* READ2 = new BitInputStream(READ);

  // Opens the file we are writing to
  WRITE.open(argv[2]);

  // Decoding all the necessary characters
  for (k = 0; k < addStores-1; k++)
  {
    // We decode the characters in the tree
    y = theTree.decode(*READ2);
    // Checking if we read in a bad character
    if (y == -1)
    {
      break;
    }
    // We write the characters into the file
    WRITE << y;
  }
  // Close the file and delete the BitInputStream we created
  READ.close();
  WRITE.close();
  delete READ2;

  return 1;
}
