#include <time.h>
#include <cstdlib>

#include "RandomOffsetMutator.h"

namespace std {
  RandomOffsetMutator::RandomOffsetMutator() {
      //Create seed
      srand(time(NULL));
      offset = rand() % 256;
    }

    unsigned char RandomOffsetMutator::mutate(unsigned char inputByte) {
      return inputByte + this->offset;
    }
}
