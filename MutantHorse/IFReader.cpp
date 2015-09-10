#include "IFReader.h"
#include <iostream>

namespace std {
	bool IFReader::open(string fn) {
		fe = new ifstream(fn, ios::in | ios::binary);
		if(fe->is_open()) {
			return true;
		}
		return false;
	}
	size_t IFReader::read(size_t N, unsigned char * buffer) {
		char tbuffer[N];
		if(fe->is_open()) {
			fe->read(tbuffer, N);
			memcpy(buffer, tbuffer, fe->gcount());
		}
		return fe->gcount();
	}
	void IFReader::close() {
		if(fe->is_open()) {
			fe->close();
		}
	}
}
