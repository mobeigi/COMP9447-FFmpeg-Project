#include <iostream>
#include <vector>

#include "FLVFormat.h"

using namespace std;

int main (int argc, const char ** argv) {

  //Check for correct number of arguments
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " <input file> <output file>";
    exit(1);
  }

  //Test FLV read/write
  FLVFormat flvFile;
  flvFile.mutate(argv[1], argv[2]);

  //Keep window alive in visual studio
#ifdef _DEBUG
    std::cin.get();
    std::cin.ignore();
#endif

  return 0;
}
