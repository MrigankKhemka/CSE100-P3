#include <fstream>
#include <vector>
#include <iostream>
#include "HCTree.hpp"

using namespace std;

int main(int argc, char** argv) {
  if(argc != 3) {
    cout << "./uncompress called with incorrect arguments." << endl;
    cout << "Usage: ./uncompress infile outfile" << endl;
    return 0;
  }

  if(argc == 3) {
    ifstream infile;
    ofstream outfile;    
    infile.open(argv[1]);
    int frequency;
    int totalFreq = 0;
    int symbols = 0;
    vector<int> freqs(256);

    cout << "Reading from file header: " << argv[1] << "... ";
    if (infile.is_open() && infile.good()) {
      for(int i = 0; i < freqs.size(); i++) {
        infile >> frequency;
        freqs[i] = frequency;
        if(frequency > 0) {
          symbols++;
          totalFreq = totalFreq + frequency;
        }
      } 
    }
    else {
      cout <<"Unable to open: " << argv[1] << endl;
      return 0;
    }
    cout << "Found " << symbols << " unique symbols in input file" << endl;
    cout << "done." << endl;

    HCTree huffman;
    cout << "Building huff" << endl;
    huffman.build(freqs); 
    cout << "Done" << endl;
    outfile.open(argv[2]);
    if (infile.is_open() && infile.good()) {
      for(int i = 0; i < totalFreq; i++) {
        outfile << (char)huffman.decode(infile);
      }
    }
    outfile.close();
    infile.close();
  }
}
