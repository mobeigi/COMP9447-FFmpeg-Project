#ifndef __Generic20__
#define __Generic20__

#include "GContainerFormat.h"

namespace std {
  class Generic20 : public GContainerFormat {
  public:
    virtual void mutate(const string input, const string output);
  };
}

#endif
