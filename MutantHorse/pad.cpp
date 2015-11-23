#include "pad.h"
#include <vector>


namespace std {
  void PaddingMutator::mutate(const string input, const string output)
  {
    //Determine total size of the file
    std::ifstream inStream(input, std::ifstream::ate | std::ifstream::binary);
    size_t totalSize = inStream.tellg();
    inStream.close();

    //Create IFReader
    IFReader ifreader;

    bool open = ifreader.open(input);
    if (!open) {
      cerr << "Error opening file at: " << input << endl;
      return;
    }

    //Create output file stream
    ofstream ofs(output, std::ofstream::binary);
	
    //Copy the original file by reading and writing the same bytes
    vector<unsigned char> initialData(totalSize);
	size_t readBytes = ifreader.read(initialData.data(), initialData.size());
	ofs.write((char *)initialData.data(), readBytes);
	
	//Append 200 zeroes to the end of the file
	vector<unsigned char> paddingData(200);
	
    for (int i = 0; i < paddingData.size(); i++) {
		paddingData[i] = 0;
	}
    ofs.write((char *)paddingData.data(), 200);

    ifreader.close();
  }
}
