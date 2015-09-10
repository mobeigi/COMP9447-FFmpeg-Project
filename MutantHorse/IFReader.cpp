#include "IFReader.h"
#include <iostream>

namespace std {
      bool IFReader::open(string fn) {
            fe = new ifstream(fn, ios::in | ios::binary);
            isO = false;

            if(fe->is_open()) {
                  fe->seekg(0, fe->end);
                  fsize = fe->tellg();
                  fe->seekg(0, fe->beg);

                  cout << fsize << endl;

                  isO = true;
            }
            return isO;
      }
      bool IFReader::read(int size) {
      }
      void IFReader::close() {
            if(isO) {
                  fe->close();
                  isO = false;
            }
      }
}
