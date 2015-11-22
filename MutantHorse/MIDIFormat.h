#ifndef __MIDIFormat__
#define __MIDIFormat__

#include "GContainerFormat.h"

namespace std {
  class MIDIFormat : public GContainerFormat {
  public:
    virtual void mutate(const string input, const string output);
    virtual void mutate(const string input, const string output, double probability) { mutate(input, output, 0.0); }  //delegate
  };
}

#endif
