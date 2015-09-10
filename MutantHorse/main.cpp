#include "IFReader.h"

using namespace std;
int main (int argc, const char ** argv) {
      IFReader * mread = new IFReader();
      mread->open(argv[1]);
      return 0;
}
