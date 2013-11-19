#include "BitOutputStream.hpp"

void BitOutputStream::flush() {
  out.put(buf);
  out.flush();
  buf = nbits = 0;
}

void BitOutputStream::writeBit(int i) {
  //Flush if bit buffer is full
  if(buf == 8) {
    flush();
  }
  //Write the least significant bit of i into the buffer
  //at the current index
  buf |= i << nbits;
  
  //Increment index
  nbits++;
  
}
