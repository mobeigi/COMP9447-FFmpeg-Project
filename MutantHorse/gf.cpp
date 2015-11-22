#include "gf.h"
#include "RandomMutator.h"
#include <time.h>
#include <vector>


namespace std {
  void GenericFull::mutate(const string input, const string output)
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

    //Mutate all bytes
    size_t readBytes = 1; //set to non-zero
    size_t totalRead = 0;

    while (readBytes != 0) {
      size_t blockSize = 128;

      //If we are going to read too much
      if (totalRead + 128 > totalSize) {
        blockSize = totalSize - totalRead;
      }

      //Read in blocks of blockSize
      vector<unsigned char> block(blockSize);

      readBytes = ifreader.read(block.data(), block.size());

      //Mutate all bytes
      RandomMutator rMutate;

      for (auto it = block.begin(); it != block.end(); ++it) {
        *it = rMutate.mutate(*it);
      }

      //Write read bytes
      ofs.write((char *)block.data(), readBytes);

      if (readBytes < 128)
        break;   //end of file

      totalRead += 128;
    }

    ifreader.close();
  }

  void GenericFull::mutate(const string input, const string output, double probability)
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

    //Mutate all bytes
    size_t readBytes = 1; //set to non-zero
    size_t totalRead = 0;

    while (readBytes != 0) {
      size_t blockSize = 128;

      //If we are going to read too much
      if (totalRead + 128 > totalSize) {
        blockSize = totalSize - totalRead;
      }

      //Read in blocks of blockSize
      vector<unsigned char> block(blockSize);

      readBytes = ifreader.read(block.data(), block.size());

      //Mutate all bytes based on probability
      RandomMutator rMutate;
      srand((unsigned)time(NULL));

      for (auto it = block.begin(); it != block.end(); ++it) {
        //Generate random number
        double generatedProbability = ((double)rand() / (double)RAND_MAX);

        if (generatedProbability < probability)
          *it = rMutate.mutate(*it);
      }

      //Write read bytes
      ofs.write((char *)block.data(), readBytes);

      if (readBytes < 128)
        break;   //end of file

      totalRead += 128;
    }

    ifreader.close();
  }
}
