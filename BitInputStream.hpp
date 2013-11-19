#include <iostream>

class BitInputStream{
  
  private:
    char buf;
    int nbits;
    std::istream& in;
  
  public:
    BitInputStream(std::istream& is) : in(is) 
    { 
      buf= 0; //Clear buffer
      nbits= 8; //Initialize bit index
    }
  
    void fill();
    int readBit();
};
