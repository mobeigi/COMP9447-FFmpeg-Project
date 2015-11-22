#include "z.h"
#include <time.h>
#include <vector>


namespace std {
  void ZeroMiddle::mutate(const string input, const string output)
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

    //Determine the lower bound and upper bound for mutations (40%-60% mark)
    size_t lower_bound = static_cast<size_t>(totalSize * 0.4);
    size_t upper_bound = static_cast<size_t>(totalSize * 0.6);


    //Write initial bytes (upto lower_bound)
    vector<unsigned char> initialData(lower_bound);

    size_t readBytes = ifreader.read(initialData.data(), initialData.size());

    //Write initial data
    ofs.write((char *)initialData.data(), readBytes);


    //Mutate all bytes within [lower_bound, upper_bound]
    vector<unsigned char> fileVector(upper_bound - lower_bound);

    readBytes = ifreader.read(fileVector.data(), fileVector.size());

    //Set all bytes to 0
    for (auto it = fileVector.begin(); it != fileVector.end(); ++it) {
      *it = 0;
    }

    //Write mutated data back
    ofs.write((char *)fileVector.data(), readBytes);


    //Write all remaining bytes unaltered [upper_bound, EOF)
    size_t totalRead = upper_bound; //upper_bound bytes read so far

    while (readBytes != 0) {
      size_t blockSize = 128;

      //If we are going to read too much
      if (totalRead + 128 > totalSize) {
        blockSize = totalSize - totalRead;
      }

      //Read in blocks of blockSize
      vector<unsigned char> block(blockSize);

      readBytes = ifreader.read(block.data(), block.size());

      //Write read bytes
      ofs.write((char *)block.data(), readBytes);

      if (readBytes < 128)
        break;   //end of file

      totalRead += 128;
    }

    ifreader.close();
  }

  void ZeroMiddle::mutate(const string input, const string output, double probability)
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

    //Determine the lower bound and upper bound for mutations (40%-60% mark)
    size_t lower_bound = static_cast<size_t>(totalSize * 0.4);
    size_t upper_bound = static_cast<size_t>(totalSize * 0.6);


    //Write initial bytes (upto lower_bound)
    vector<unsigned char> initialData(lower_bound);

    size_t readBytes = ifreader.read(initialData.data(), initialData.size());

    //Write initial data
    ofs.write((char *)initialData.data(), readBytes);


    //Mutate all bytes within [lower_bound, upper_bound]
    vector<unsigned char> fileVector(upper_bound - lower_bound);

    readBytes = ifreader.read(fileVector.data(), fileVector.size());

    //Set some bytes to 0 based on probability
    srand((unsigned)time(NULL));

    for (auto it = fileVector.begin(); it != fileVector.end(); ++it) {
      //Generate random number
      double generatedProbability = ((double)rand() / (double)RAND_MAX);

      if (generatedProbability < probability)
        *it = 0;
    }

    //Write mutated data back
    ofs.write((char *)fileVector.data(), readBytes);


    //Write all remaining bytes unaltered [upper_bound, EOF)
    size_t totalRead = upper_bound; //upper_bound bytes read so far

    while (readBytes != 0) {
      size_t blockSize = 128;

      //If we are going to read too much
      if (totalRead + 128 > totalSize) {
        blockSize = totalSize - totalRead;
      }

      //Read in blocks of blockSize
      vector<unsigned char> block(blockSize);

      readBytes = ifreader.read(block.data(), block.size());

      //Write read bytes
      ofs.write((char *)block.data(), readBytes);

      if (readBytes < 128)
        break;   //end of file

      totalRead += 128;
    }

    ifreader.close();
  }
}
