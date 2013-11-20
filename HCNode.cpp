//------------------------------------------------
// Filename: HCNode.cpp
// Author: Jimmy Li
// Date: 11/19/2013
// Rev-Date: 11/19/2013
//
// Description: Huffman tree node class 
//
//--------------------------------------------

#include "HCNode.hpp"
#include <iostream>

//------------------------------------------------------------------
// operator<(const HCNode& other): Compares priority of nodes  
//
// Input: const HCNode& other
// Output: bool
//-------------------------------------------------------------------

bool HCNode::operator<(const HCNode& other) {
  if(count != other.count) {
    return count > other.count;
  }
  return symbol < other.symbol;
}
