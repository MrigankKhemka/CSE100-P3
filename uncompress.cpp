//------------------------------------------------
// Filename: uncompress.cpp
// Author: Jimmy Li
// Date: 11/19/2013
// Rev-Date: 11/19/2013
//
// Description: Uncompress class, used to uncompress files 
//
//-------------------------------------------------

#include <fstream>
#include <vector>
#include <iostream>
#include "HCTree.hpp"

using namespace std;

//------------------------------------------------------------------
// main(int argc, char** argv): the program's main routine 
//
// Input: int argc, char** argv 
// Output: int
//-------------------------------------------------------------------

int main(int argc, char** argv) {

  //Exits if uncompress is not called with two arguments
  if(argc != 3) {
    cout << "./uncompress called with incorrect arguments." << endl;
    cout << "Usage: ./uncompress infile outfile" << endl;
    return 0;
  }

  //Begins if uncompress is called with two arguments
  if(argc == 3) {
    ifstream infile;
    ofstream outfile;    
    int frequency;
    int symbols = 0;
    int totalBytes = 0;
    vector<int> freqs(256);
   
    //Read the compressed file's header and recreate the frequency vector 
    infile.open(argv[1], ios::binary);
    cout << "Reading from file header: " << argv[1] << endl;
    if (infile.is_open() && infile.good()) {
      for(int i = 0; i < freqs.size(); i++) {
        infile >> frequency;
        freqs[i] = frequency;
        if(frequency > 0) {
          symbols++;
          totalBytes += frequency;
        }
      } 
    }
    else {
      cout <<"Unable to open: " << argv[1] << endl;
      return 0;
    }

    cout << "Found " << symbols << " unique symbols in input file" << endl;
    cout << "done." << endl;

    //Rebuild huffman tree
    HCTree huffman;
    cout << "Building huffman tree" << endl;
    huffman.build(freqs); 
    cout << "Done" << endl;
   
    //Continue scanning the input file after the header and decode bit by bit.
    //Then write the characters to the outfile specified in argument 2.
    outfile.open(argv[2], ios::binary);
    BitInputStream bitInput = BitInputStream(infile);

    cout << "Uncompressing..." << endl;
    for(int i = 0; i < totalBytes; i++) {
      if(infile.is_open()) {
        if(!infile.good()) break;
        if(infile.eof()) break;
        outfile << (char)huffman.decode(bitInput);
      }
    }

    cout << "Done" << endl;
    outfile.close();
    infile.close();
  }
}
