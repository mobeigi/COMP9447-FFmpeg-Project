#ifndef __IFReader__
#define __IFReader__

namespace std {
      class IFReader;
}

#include <fstream>

namespace std {
      class IFReader  {
      private:
            ifstream * fe;
            bool isO;
            int fsize;
      public:
            bool open(string fn);
            bool read(int size);
            void close();
      };
}

#endif
