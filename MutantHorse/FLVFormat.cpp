#include "FLVFormat.h"

#include <vector>

namespace std {
  void FLVFormat::mutate(const string input, const string output) {
    //Create IFReader
    IFReader ifreader;
    
    bool open = ifreader.open(input);
    if (!open) {
      cerr << "Error opening file at: " << input << endl;
      return;
    }

  //Create output file stream
  ofstream ofs(output, std::ofstream::binary);

  //Read FLV header
  vector<unsigned char> flvheader(9);

  size_t read = ifreader.read(flvheader.size(), flvheader.data());

  //Write FLV header
  ofs.write((char *)flvheader.data(), flvheader.size());

  }
  void FLVFormat::generate() {
    //Todo
  }
}
