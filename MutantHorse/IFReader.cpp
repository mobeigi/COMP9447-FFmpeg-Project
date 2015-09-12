#include "IFReader.h"

namespace std {
	bool IFReader::open(const string fn) {
		fe = new ifstream(fn, ios::in | ios::binary);
		if(fe->is_open()) {
			return true;
		}
		return false;
	}

	size_t IFReader::read(unsigned char * buffer, const size_t N) {
		vector<char> tbuffer(N);
		if(fe->is_open()) {
			memset(buffer, 0, N);
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
