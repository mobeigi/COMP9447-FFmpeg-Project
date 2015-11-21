#include "WAVFormat.h"
#include "RandomMutator.h"
#include "RandomOffsetMutator.h"
#include <vector>


namespace std {
  void WAVFormat::mutate(const string input, const string output)
  {
    //Create IFReader
    IFReader ifreader;

    bool open = ifreader.open(input);
    if (!open) {
      cerr << "Error opening file at: " << input << endl;
      return;
    }

    //Create output file stream
    ofstream ofs(output, std::ofstream::binary);

    //Read WAV header
    vector<unsigned char> wavheader(44);

    size_t readBytes = ifreader.read(wavheader.data(), wavheader.size());

    //Write WAV header
    ofs.write((char *)wavheader.data(), readBytes);

    size_t dataSectionSize = 0;

    //Get size of data section
    for (int i = 43; i >= 40; --i) { //bytes at index 41-44 (4 bytes) contain size, big endian
      dataSectionSize = (dataSectionSize << 8) + (wavheader[i]);
    }

    //For the remainder of the wav file (data portion)
    size_t totalRead = 0;

    while (readBytes != 0) {
      size_t blockSize = 128;

      //If we are going to read too much
      if (totalRead + 128 > dataSectionSize) {
        blockSize = dataSectionSize - totalRead;
      }

      //Read in blocks of blockSize
      vector<unsigned char> block(blockSize);

      readBytes = ifreader.read(block.data(), block.size());

      //Mutate bytes
      RandomMutator mutator;

      for (auto it = block.begin(); it != block.end(); ++it) {
        *it = mutator.mutate(*it);
      }

      //Write read bytes
      ofs.write((char *)block.data(), readBytes);

      if (readBytes < 128)
        break;   //end of file

      totalRead += 128;
    }

  }
}
