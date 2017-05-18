/*
 * Author: Rizwan Khan
 * CSE Login: cs100sgv
 * PID: A12236946
 * Email: rikhan@ucsd.edu
 */

#ifndef BITOUTPUTSTREAM_H
#define BITOUTPUTSTREAM_H

#include <iostream>

class BitOutputStream {
  private:
    // One byte buffer of bits
    unsigned char buf;
    // How many bits have been written to buf
    unsigned int nbits;
    // Reference to output stream to use
    std::ostream & out;

  public:
    /* Initialize a BitOutputStream that will use the given ostream
     * for output */
    BitOutputStream(std::ostream & os) : out(os), buf(0), nbits(0) {}
    // Clear buffer and bit counter

  /* Send the buffer to the output, and clear it */
    /*void flush() 
    {
      out.put(buf);
      out.flush();
      buf = nbits = 0;
    }*/

  void flush();

  void writeBit(unsigned int i);
};
#endif
