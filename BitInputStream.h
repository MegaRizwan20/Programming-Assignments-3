/*
 * Author: Rizwan Khan
 * CSE Login: cs100sgv
 * PID: A12236946
 * Email: rikhan@ucsd.edu
 */

#ifndef BITINPUTSTREAM_H
#define BITINPUTSTREAM_H

#include <istream>

class BitInputStream {
  private:
    // The one byte buffer of the bits
    unsigned char buf;
    // The number of bits that have been read from the buf
    unsigned int nbits;
    // The input stream that is being used
    std::istream & in;

  public:
   /* Initialize a BitInputStream that will use the given istream
    * for input */
   BitInputStream(std::istream & is) : in(is) {
     buf = 0;
     nbits = 8;
   }

   // Used to fill up the bits
   void fill();

   // Used to read the bits
   unsigned int readBit();
};
#endif
