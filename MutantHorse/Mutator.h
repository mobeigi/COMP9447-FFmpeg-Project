#ifndef __MutatorInterface__
#define __MutatorInterface__

namespace std {
  class Mutator {
  public:
    //Takes in a byte, mutates it and returns a new byte
    virtual unsigned char mutate(unsigned char inputByte) = 0;
  };
}

#endif
