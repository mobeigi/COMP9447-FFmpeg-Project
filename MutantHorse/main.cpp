#include <iostream>
#include <vector>
#include <algorithm>
#include <string> 

#include "FLVFormat.h"
//#include "easylogging.h"

//INITIALIZE_EASYLOGGINGPP

#define PROCESS_MUTATE "mutate"
#define PROCESS_MUTATE_FLAG "m"

using namespace std;

int main (int argc, const char ** argv) {

  //Check for correct number of arguments
  if (argc != 4) {
    cerr << "Usage: " << argv[0] << " <input file> <output file> <fuzz_mode>" << endl;
    exit(1);
  }

  //Set input/output paths
  string inputFile = argv[1];
  string outputFile = argv[2];
  string fuzzMode = argv[3];
  std::transform(fuzzMode.begin(), fuzzMode.end(), fuzzMode.begin(), ::tolower); //convert to lower case

  //Detect file extensions
  string inputExt = inputFile.substr(inputFile.find_last_of(".") + 1);
  string outputExt = outputFile.substr(outputFile.find_last_of(".") + 1);

  //Ensure extensions are same
  if (inputExt != outputExt) {
    cerr << "Input and output extensions must be the same." << endl;
    exit(1);
  }

  //Ensure extensions is supported
  if (inputExt == "flv") {
    FLVFormat flvFile;

    if (fuzzMode == PROCESS_MUTATE || fuzzMode == PROCESS_MUTATE_FLAG) {
      flvFile.mutate(inputFile, outputFile);
    }
  }
  //Unsupported format
  else {
    cerr << "Provided file extention is not supported." << endl;
    exit(1);
  }

  //Keep window alive in visual studio
#ifdef _DEBUG
    std::cin.get();
    std::cin.ignore();
#endif

  return 0;
}
