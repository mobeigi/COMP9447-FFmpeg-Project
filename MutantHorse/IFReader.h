#ifndef __IFReader__
#define __IFReader__

#include <fstream>

namespace std {
	class IFReader  {
	private:
		ifstream * fe;
		size_t fsize;
	public:
		bool open(string);
		size_t read(size_t, unsigned char *);
		void close();
	};
}

#endif
