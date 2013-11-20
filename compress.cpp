//------------------------------------------------
// Filename: compress.cpp
// Author: Jimmy Li
// Date: 11/19/2013
// Rev-Date: 11/19/2013
//
// Description: Compress class, used to compress files 
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
  
  //Exits if compress is not called with two arguments
  if(argc != 3) {
    cout << "./compress called with incorrect arguments." << endl;
    cout << "Usage: ./compress infile outfile" << endl;
    return 0;
  }

  //Begins if compress is called with two arguments
  if(argc == 3) {
    ifstream infile;
    ofstream outfile;    
    infile.open(argv[1], ios::binary);
    char nextChar;
    int symbols = 0;
    //Vector of ACSII values storing occurences 
    vector<int> freqs(256);
    cout << "Reading from file: " << argv[1] << "... ";

    //Scans the entire file and stores the number of occurences for each
    //symbol in the vector
    while(1) {
      if (infile.is_open()) {
        nextChar = (char)infile.get();
        if(infile.eof()) break;
        if(!infile.good()) break;
        for(int i = 0; i < freqs.size(); i++) {
          if(nextChar == i) {
            freqs[i]++;
            //Counts the number of unique symbols in the file
            if(freqs[i] == 1) {
              symbols++;
            }
          }
        }
      }
      else {
        cout <<"Unable to open: " << argv[1] << endl;
        return 0;
      }
    }
    infile.close();

    cout << "Found " << symbols << " unique symbols in input file" << endl;
    cout << "done." << endl;

    //Create huffman tree based on the number of occurences 
    HCTree huffman;
    cout << "Building huff" << endl;
    huffman.build(freqs); 
    cout << "Done" << endl;
    
    //Write the header in the output file, which will be used to recreate
    //the frequency vector in the uncompress class to rebuild the huffman
    //tree
    outfile.open(argv[2], ios::binary);
    if(outfile.is_open()) {
      for(int i=0;i<freqs.size();i++) {
        outfile << " " << freqs[i];
      } 
    }

    //Reopen the input file
    ifstream infile2;
    infile2.open(argv[1], ios::binary);
    BitOutputStream bitOut = BitOutputStream(outfile);
    //Scan through the entire file and encode bit by bit
    while(1) {
      if (infile2.is_open()) {
        nextChar = (char)infile2.get();
        if(infile2.eof()) break;
        if(!infile2.good()) break;
        huffman.encode(nextChar, bitOut);
      }
    }
    outfile.close();
    infile2.close();
  }
}
