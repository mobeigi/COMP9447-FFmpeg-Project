#ifndef __PaddingMutator__
#define __PaddingMutator__

#include "GContainerFormat.h"

namespace std {
  class PaddingMutator : public GContainerFormat {
  public:
    virtual void mutate(const string input, const string output);
    virtual void mutate(const string input, const string output, double probability) { mutate(input, output, 0.0); }  //delegate
  };
}

#endif