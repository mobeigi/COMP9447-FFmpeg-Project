#ifndef __AVIFormat__
#define __AVIFormat__

namespace std {
	class AVIFormat;
}

#include "GContainerFormat.h"

namespace std {
	class AVIFormat : public GContainerFormat {
	public:
		AVIFormat();
		void mutate();
		void generate();
	};
}

#endif
