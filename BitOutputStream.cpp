/*
 * Author: Rizwan Khan
 * CSE Login: cs100sgv
 * PID: A12236946
 * Email: rikhan@ucsd.edu
 */

#include "BitOutputStream.h"
#include <iostream>
#include <fstream>
//#include <ifstream>

using namespace std;

// This method sends the buffer to the output and clears it.
// This is used to make sure we have an empty buffer when the
// buffer fills up
void BitOutputStream::flush()
{
  out.put(buf);
  out.flush();
  buf = nbits = 0;
}

void BitOutputStream::writeBit(unsigned int i)
{
  // This checks if the buffer is full and then we clear it out
  //cout << nbits << " BEFORE IF " << endl;
  if (nbits == 8)
  {
    flush();
  }
  // Place the bits into the buffer and increment up the number of bits
  // we have plus how much we are shifting it by
  //cout << nbits << endl;
  //buf = buf | ((i & 1) << nbits);
  // buf = buf | ((i & 1) << (7 - nbits));
  buf = buf | (i << (7 - nbits));
  nbits++;
}
