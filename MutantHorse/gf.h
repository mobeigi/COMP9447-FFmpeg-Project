#ifndef __GenericFull__
#define __GenericFull__

#include "GContainerFormat.h"

namespace std {
  class GenericFull : public GContainerFormat {
  public:
    virtual void mutate(const string input, const string output);
    virtual void mutate(const string input, const string output, double probability);
  };
}

#endif
