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
 * Purpose: Used to read in the files and from those files we 
 * will be encoding the tree into bits by using BitOutputStream
 */
int main(int argc, char* argv[])
{
  // Used to read in the file
  ifstream READ;
  // Used to write into the file
  ofstream WRITE;
  // The tree we are trying to build
  HCTree theTree;
  // The vector that we are making
  std::vector<unsigned int> treeVec(256, 0);
  // Used to store the necessary elements into the vector
  unsigned int k = 0;
  // The character that we are reading in
  unsigned char y;

  // Open the file that I am reading in
  READ.open(argv[1]);

  // Read through the file and increment when I find the
  // character
  while (1)
  {
    // Get the characters from the file
    y = READ.get();
    // Increment what is in the vector
    treeVec[y]++;
    // Check if we are done reading in the file
    if (!READ.good())
    {
      break;
    }
  }
  // Close what we just finished reading
  READ.close();
  // Build the tree based on what is in the vector
  theTree.build(treeVec);

  // Open up where we are writing to
  WRITE.open(argv[2]);
  // Loop through the vector and add to the ofstream
  for (k = 0; k < treeVec.size(); k++)
  {
    WRITE << treeVec[k] << endl;
  }
  // Open the file and initialize a new BitOutputStream
  READ.open(argv[1]);
  BitOutputStream* WRITE2 = new BitOutputStream(WRITE);

  // Read the input instream to get the characters and encode the tree
  while (1)
  {
    // Gets the characters
    y = READ.get();   
    // Starts encoding the tree with the received characters
    theTree.encode((byte)y, *WRITE2);

    // Checks if we got to the end of a file
    if (!READ.good())
    {
      break;
    }
  }

  // Flush the outputstream of bits we are using and close the files
  WRITE2->flush();
  READ.close();
  WRITE.close();
  // Delete the object that we allocated
  delete WRITE2;

  return 1;
}
