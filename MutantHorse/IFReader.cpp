#include "IFReader.h"
#include <iostream>
#include <vector>

namespace std {
	bool IFReader::open(string fn) {
		fe = new ifstream(fn, ios::in | ios::binary);
		if(fe->is_open()) {
			return true;
		}
		return false;
	}

	size_t IFReader::read(size_t N, unsigned char * buffer) {
		vector<char> tbuffer(N);
		if(fe->is_open()) {
			fe->read(tbuffer.data(), N);
			memcpy(buffer, tbuffer.data(), fe->gcount());
      return fe->gcount(); //return number of bytes read
		}

		return 0; //read no bytes
	}

	void IFReader::close() {
		if(fe->is_open()) {
			fe->close();
		}
	}
}
