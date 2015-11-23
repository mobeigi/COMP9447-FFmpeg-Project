#ifndef __IFReader__
#define __IFReader__

#include <fstream>
#include <vector>
#include <string.h>

namespace std {
	class IFReader  {
	private:
		ifstream * fe;
		size_t fsize;
	public:
		bool open(const string);
		size_t read(unsigned char *, const size_t);
		void close();
	};
}

#endif
