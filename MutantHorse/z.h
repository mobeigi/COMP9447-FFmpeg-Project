#ifndef __ZeroMiddle__
#define __ZeroMiddle__

#include "GContainerFormat.h"

namespace std {
  class ZeroMiddle : public GContainerFormat {
  public:
    virtual void mutate(const string input, const string output);
    virtual void mutate(const string input, const string output, double probability);
  };
}

#endif
