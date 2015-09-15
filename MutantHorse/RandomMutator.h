#ifndef __RandomMutator__
#define __RandomMutator__

#include "Mutator.h"

namespace std {
  class RandomMutator : public Mutator {
  public:
    //Takes in a byte, mutates it and returns a new byte
    virtual unsigned char mutate(unsigned char inputByte) const;
  };
}

#endif
