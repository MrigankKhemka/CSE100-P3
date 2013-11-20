//------------------------------------------------
// Filename: BitOutputStream.hpp
// Author: Jimmy Li
// Date: 11/19/2013
// Rev-Date: 11/19/2013
//
// Description: Bit by bit output class. Used
//              lecture 16 as guideline 
//
//-------------------------------------------------

#include "BitOutputStream.hpp"

/** Send the buffer to the output and clear it*/
void BitOutputStream::flush() {
  out.put(buf);
  out.flush();
  buf = nbits = 0;
}

/** Write the least significant bit of the argument to
  * the bit buffer, and increment the bit buffer index.
  * Flush buffer first if it is full.
  */
void BitOutputStream::writeBit(int i) {
  //Flush if bit buffer is full
  if(nbits == 8) {
    flush();
  }
  //Write the least significant bit of i into the buffer
  //at the current index
  buf |= i << nbits;
  //Increment index
  nbits++;
  
}
