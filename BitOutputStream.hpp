#include <iostream>

class BitOutputStream {
  private:
    char buf; //one byte buffer of bits
    int nbits; //# of bits written to buf
    std::ostream& out;
  public:
    
    BitOutputStream(std::ostream& os) : out(os), buf(0), nbits(0) {}
    
    void flush();
    void writeBit(int i);
    
};
