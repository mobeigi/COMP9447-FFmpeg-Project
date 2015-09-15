#ifndef __RandomOffsetMutator__
#define __RandomOffsetMutator__

#include "Mutator.h"

namespace std {
  class RandomOffsetMutator : public Mutator {
  public:
    RandomOffsetMutator::RandomOffsetMutator();

    //Takes in a byte, mutates it and returns a new byte
    virtual unsigned char mutate(unsigned char inputByte);

  private:
    unsigned char offset;
  };
}

#endif
