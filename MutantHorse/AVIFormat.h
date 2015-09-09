#ifndef __AVIFormat__
#define __AVIFormat__

namespace std {
      class AVIFormat;
}

#include "GContainerFormat.h"

namespace std {
      class AVIFormat : public GContainerFormat {
      public:
            void mutate();
            void generate();

      private:
            ifstream * fe;
      };
}

#endif __AVIFormat__
