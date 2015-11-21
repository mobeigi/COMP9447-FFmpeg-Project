#ifndef __MIDIFormat__
#define __MIDIFormat__

#include "GContainerFormat.h"

namespace std {
  class MIDIFormat : public GContainerFormat {
  public:
    virtual void mutate(const string input, const string output);
  };
}

#endif
