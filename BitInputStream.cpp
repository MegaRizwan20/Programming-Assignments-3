/*
 * Author: Rizwan Khan
 * CSE Login: cs100sgv
 * PID: A12236946
 * Email: rikhan@ucsd.edu
 */

#include "BitInputStream.h"
#include <istream>
#include <iostream>
#include <fstream>
//#include <ifstream>

using namespace std;

void BitInputStream::fill()
{
  // Clear the buffer
  buf = in.get();
  // Initialize the bit index
  nbits = 0;
}

unsigned int BitInputStream::readBit()
{
  // Checking the bit that we need
  unsigned int needBit = 0;
  // If the buffer is read we want to get them and reset the nbits
  if (nbits == 8)
  {
    fill();
  }

  // Check if the bit read is 0 so we return 0
  needBit = (buf << nbits) & (1 << 7);
  // Increment the number of bits
  nbits++;
  // Return 1 if this is equal to 1
  if ((needBit>>7) == 1)
  {
    return 1;
  }
  // Return 0 if this is equal to 0
  else if ((needBit>>7) == 0)
  {
    return 0;
  }
}
