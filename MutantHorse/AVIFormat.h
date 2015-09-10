#ifndef __AVIFormat__
#define __AVIFormat__

#include "GContainerFormat.h"

namespace std {
  class AVIFormat : public GContainerFormat {
    public:
    virtual void mutate(const string input, const string output);
    virtual void generate();
  };
}

#endif
