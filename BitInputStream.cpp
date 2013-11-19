#include "BitInputStream.hpp"

void BitInputStream::fill()
{
  buf = in.get();
  nbits = 0;
}

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
