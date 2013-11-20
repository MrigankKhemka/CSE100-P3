//------------------------------------------------
// Filename: BitOutputStream.hpp
// Author: Jimmy Li
// Date: 11/19/2013
// Rev-Date: 11/19/2013
//
// Description: Bit by bit output interface. Used
//              lecture 16 as guideline 
//
//-------------------------------------------------

#include <iostream>

class BitOutputStream {
  private:
    char buf; //one byte buffer of bits
    int nbits; //# of bits written to buf
    std::ostream& out; //reference to output stream to use
  public:
    
    /** Initialize a BitOutputStream that will use
      * the given ostream for output.
      */
    BitOutputStream(std::ostream& os) : out(os), buf(0), nbits(0) {}
    
    /** Send the buffer to the output and clear it*/
    void flush();

    /** Write the least significant bit of the argument to
      * the bit buffer, and increment the bit buffer index.
      * Flush buffer first if it is full.
      */
    void writeBit(int i);
    
};
