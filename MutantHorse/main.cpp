#include "IFReader.h"
#include <iostream>
#include <vector>

using namespace std;

int main (int argc, const char ** argv) {

  //Check for correct number of arguments
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <input file> <output file>";
    exit(1);
  }

  IFReader * mread = new IFReader();
  mread->open(argv[1]);

  size_t N = 8;
  vector<unsigned char> buffer(N);

  for (unsigned i = 0; i != 20; i++ ) {
  	size_t count = mread->read(N, buffer.data());
    cout << buffer.data() << endl;
  }
	mread->close();

  //Keep window alive in visual studio
#ifdef _DEBUG
    std::cin.get();
    std::cin.ignore();
#endif

  return 0;
}
