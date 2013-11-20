//------------------------------------------------
// Filename: BitInputStream.cpp
// Author: Jimmy Li
// Date: 11/19/2013
// Rev-Date: 11/19/2013
//
// Description: Bit by bit input class. Used
//              lecture 16 as guideline 
//
//-------------------------------------------------
#include "BitInputStream.hpp"

/** Fill the buffer from the input */
void BitInputStream::fill()
{
  buf = in.get();
  nbits = 0;
}

/** Read the next bit from the bit buffer.
  * Fill the buffer from the input stream first if needed
  * Return 1 if the bit read is 1
  * Return 0 if the bit read is 0
  */
int BitInputStream::readBit()
{
  //If all bits in buffer all read, fill the buffer first
  if(nbits == 8) {
    fill();
  }
  
  //Get bit at location in bit buffer and return int
  bool bit = buf & (1 << nbits);
  nbits++;
  if(bit == true) {
    return 1;
  }
  else {
    return 0;
  }
}
