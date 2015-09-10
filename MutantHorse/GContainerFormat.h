#ifndef __GContainerFormat__
#define __GContainerFormat__

#include <string>
#include "IFReader.h"
#include <iostream>
#include <fstream>

namespace std {
	class GContainerFormat {
	public:
		virtual void mutate(const string input, const string output) = 0;
		virtual void generate() = 0;
	};
}

#endif
