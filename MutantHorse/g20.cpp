#include "g20.h"
#include "RandomMutator.h"
#include <time.h>
#include <vector>


namespace std {
  void Generic20::mutate(const string input, const string output)
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

    //Determine the upper bound for mutations (20% mark)
    size_t upper_bound = static_cast<size_t>(totalSize * 0.2);

    //Pick two random points
    size_t start, end;
    start = end = rand() % upper_bound;

    //Ensure end and start are not the same (minimum 1 byte mutated)
    while (end == start) {
      end = rand() % upper_bound;
    }

    //Ensure start and end are logical
    if (start > end) {
      swap(start, end);
    }

    //Write initial bytes (upto start)
    vector<unsigned char> initialData(start);

    size_t readBytes = ifreader.read(initialData.data(), initialData.size());

    //Write initial data
    ofs.write((char *)initialData.data(), readBytes);


    //Mutate all bytes within [start, end]
    vector<unsigned char> fileVector(end - start);

    readBytes = ifreader.read(fileVector.data(), fileVector.size());

    //Mutate all bytes
    RandomMutator rMutate;

    for (auto it = fileVector.begin(); it != fileVector.end(); ++it) {
      *it = rMutate.mutate(*it);
    }

    //Write mutated data back
    ofs.write((char *)fileVector.data(), readBytes);


    //Write all remaining bytes unaltered [end, EOF)
    size_t totalRead = end; //end bytes read so far

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

  void Generic20::mutate(const string input, const string output, double probability)
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

    //Determine the upper bound for mutations (20% mark)
    size_t upper_bound = static_cast<size_t>(totalSize * 0.2);

    //Pick two random points
    size_t start, end;
    start = end = rand() % upper_bound;

    //Ensure end and start are not the same (minimum 1 byte mutated)
    while (end == start) {
      end = rand() % upper_bound;
    }

    //Ensure start and end are logical
    if (start > end) {
      swap(start, end);
    }

    //Write initial bytes (upto start)
    vector<unsigned char> initialData(start);

    size_t readBytes = ifreader.read(initialData.data(), initialData.size());

    //Write initial data
    ofs.write((char *)initialData.data(), readBytes);


    //Mutate all bytes within [start, end]
    vector<unsigned char> fileVector(end - start);

    readBytes = ifreader.read(fileVector.data(), fileVector.size());

    //Mutate bytes based on probability
    RandomMutator rMutate;
    srand((unsigned)time(NULL));

    for (auto it = fileVector.begin(); it != fileVector.end(); ++it) {
      //Generate random number
      double generatedProbability = ((double)rand() / (double)RAND_MAX);

      if (generatedProbability < probability)
        *it = rMutate.mutate(*it);
    }

    //Write mutated data back
    ofs.write((char *)fileVector.data(), readBytes);


    //Write all remaining bytes unaltered [end, EOF)
    size_t totalRead = end; //end bytes read so far

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
