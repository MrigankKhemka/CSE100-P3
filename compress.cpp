#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  if(argc != 3) {
    cout << "./compress called with incorrect arguments." << endl;
    cout << "Usage: ./compress infile outfile" << endl;
    return 0;
  }
  if(argc == 3) {
    ifstream infile;    
    infile.open(argv[1]);
    char nextChar;
    int symbols = 0;
    vector<int> freqs(256);
    cout << "Reading from file" << argv[1] << "...";
    while(1) {
      nextChar = (char)infile.get();
      if(infile.eof()) break;
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
    cout << "done." << endl;
    cout << "Found " << symbols << " unique symbols in input file" << endl;
    infile.close();
  }
}
