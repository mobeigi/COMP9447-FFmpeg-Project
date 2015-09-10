#include "IFReader.h"
#include <iostream>
using namespace std;

//jason is a nooo000b

int main (int argc, const char ** argv) {
  IFReader * mread = new IFReader();
  mread->open(argv[1]);

  size_t N = 8;
  unsigned char buffer[N];
  for (unsigned i = 0; i != 20; i++ ) {
  	size_t count = mread->read(N, buffer);
    cout << buffer << endl;
  }
	mread->close();
  return 0;
}
