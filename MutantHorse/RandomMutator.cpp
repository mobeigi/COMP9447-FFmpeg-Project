#include <time.h>
#include <cstdlib>

#include "RandomMutator.h"

namespace std {
    RandomMutator::RandomMutator() {
      //Create seed
      srand(time(NULL));
    }

    unsigned char RandomMutator::mutate(unsigned char inputByte) {
      return rand() % 256;
    }
}
