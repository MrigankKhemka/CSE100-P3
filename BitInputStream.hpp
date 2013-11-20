//------------------------------------------------
// Filename: BitInputStream.hpp
// Author: Jimmy Li
// Date: 11/19/2013
// Rev-Date: 11/19/2013
//
// Description: Bit by bit input interface. Used
//              lecture 16 as guideline 
//
//-------------------------------------------------

#include <iostream>

class BitInputStream{
  
  private:
    char buf; //one byte buffer of bits
    int nbits; //number of bits read from buf
    std::istream& in; //input stream used
  
  public:
   
    /** Initialize a BitInputStream that will use the given istream
      * for input
      */
    BitInputStream(std::istream& is) : in(is) 
    { 
      buf= 0; //Clear buffer
      nbits= 8; //Initialize bit index
    }
    
    /** Fill the buffer from the input */
    void fill();

    /** Read the next bit from the bit buffer.
      * Fill the buffer from the input stream first if needed
      * Return 1 if the bit read is 1
      * Return 0 if the bit read is 0
      */
    int readBit();
};
