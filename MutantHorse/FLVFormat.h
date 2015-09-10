#ifndef __FLVFormat__
#define __FLVFormat__

#include "GContainerFormat.h"

namespace std {
  class FLVFormat : public GContainerFormat {
  public:
    virtual void mutate(const string input, const string output);
    virtual void generate();
  };
}

#endif
