#include "Mutator.h"

#include <time.h>
#include <cstdlib>

namespace std {
  class RandomMutator : public Mutator {
  public:

    RandomMutator::RandomMutator() {
      //Create seed
      srand(time(NULL));
    }

    unsigned char mutate(unsigned char inputByte) const {
      return rand() % 256;
    }
  };
}
