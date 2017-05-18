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
  unsigned int needBit = 0;
  //unsigned char mask = buf;
  //mask = mask & 0;
  //mask = mask | 1;
  //mask = mask << nbits;
  // If the buffer is read we want to get them and reset the nbits
  if (nbits == 8)
  {
    fill();
  }
  //mask = mask | 1;
  //mask = mask >> nbits;
  //mask = mask & 1;
  //return mask;

  // Check if the bit read is 0 so we return 0
  needBit = (buf << nbits) & (1 << 7);
  
  //needBit = (buf << nbits) & 1;
  //if (((buf >> nbits) & 1) == 0)
  //if (((buf << (7-nbits)) & 1) == 0)
  //{
  //  nbits++;
  //  return 0;
  //}
  // Check if the bit read is 1 so we return 1
  //else if (((buf >> nbits) & 1) == 1)
  //else if (((buf << (7-nbits)) & 1) == 1)
  //{
  //  nbits++;
  //  return 1;
  //}
  nbits++;
  //if (needBit == 1)
  if ((needBit>>7) == 1)
  {
    return 1;
  }
  //else if (needBit == 0)
  else if ((needBit>>7) == 0)
  {
    return 0;
  }
}
