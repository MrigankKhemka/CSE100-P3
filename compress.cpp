#include <fstream>
#include <vector>
#include <iostream>
#include "HCTree.hpp"

using namespace std;

int main(int argc, char** argv) {
  if(argc != 3) {
    cout << "./compress called with incorrect arguments." << endl;
    cout << "Usage: ./compress infile outfile" << endl;
    return 0;
  }
  if(argc == 3) {
    ifstream infile;
    ofstream outfile;    
    infile.open(argv[1], ios::binary);
    char nextChar;
    int symbols = 0;
    vector<int> freqs(256);
    cout << "Reading from file: " << argv[1] << "... ";
    while(1) {
      if (infile.is_open()) {
        nextChar = (char)infile.get();
        if(infile.eof()) break;
        if(!infile.good()) break;
        for(int i = 0; i < freqs.size(); i++) {
          if(nextChar == i) {
            freqs[i]++;
            if(freqs[i] == 1) {
              symbols++;
            }
            //cout << "i" << i << endl;
            //cout << "freqs" <<freqs[i] << endl;
          }
        }
       // cout << nextChar;
      }
      else {
        cout <<"Unable to open: " << argv[1] << endl;
        return 0;
      }
    }
    infile.close();
    cout << "Found " << symbols << " unique symbols in input file" << endl;
    cout << "done." << endl;

    HCTree huffman;
    cout << "Building huff" << endl;
    huffman.build(freqs); 
    cout << "Done" << endl;
    
    outfile.open(argv[2], ios::binary);
    if(outfile.is_open()) {
      for(int i=0;i<freqs.size();i++) {
        outfile << freqs[i] << " ";
      }
      outfile << "\n";
    }
    infile.open(argv[1], ios::binary);
    BitOutputStream bitOut = BitOutputStream(outfile);
    while(1) {
      if (infile.is_open()) {
        nextChar = (char)infile.get();
        if(infile.eof()) break;
        if(!infile.good()) break;
        huffman.encode(nextChar, bitOut);
      }
    }
    outfile.close();
    infile.close();
  }
}
