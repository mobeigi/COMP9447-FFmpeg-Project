#ifndef __PaddingMutator__
#define __PaddingMutator__

#include "GContainerFormat.h"

namespace std {
  class PaddingMutator : public GContainerFormat {
  public:
    virtual void mutate(const string input, const string output);
  };
}

#endif
