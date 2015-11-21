#ifndef __WAVFormat__
#define __WAVFormat__

#include "GContainerFormat.h"

namespace std {
  class WAVFormat : public GContainerFormat {
  public:
    virtual void mutate(const string input, const string output);
  };
}

#endif
