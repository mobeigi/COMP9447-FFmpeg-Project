#include <iostream>
#include <vector>
#include <algorithm>
#include <string> 

#include "FLVFormat.h"
#include "WAVFormat.h"
#include "MIDIFormat.h"
#include "gf.h"
#include "g20.h"

//#include "easylogging.h"

using namespace std;

int main (int argc, const char ** argv) {

  //Check for correct number of arguments
  if (argc < 3 || argc > 5) {
    cerr << "Usage: " << argv[0] << " <input file> <output file> <generic mutator flag> <probability>" << endl;
    exit(1);
  }

  //Set input/output paths
  string inputFile = argv[1];
  string outputFile = argv[2];

  //Detect file extensions
  string inputExt = inputFile.substr(inputFile.find_last_of(".") + 1);
  string outputExt = outputFile.substr(outputFile.find_last_of(".") + 1);

  //Check if input file exists
  std::ifstream infile(inputFile);
  if (!infile.good()) {
    cerr << "Input file does not exist." << endl;
    exit(1);
  }
  infile.close();

  //Ensure extensions are same
  if (inputExt != outputExt) {
    cerr << "Input and output extensions must be the same." << endl;
    exit(1);
  }

  //Check if we should use generic mutators
  if (argc >= 4) {
    string generic_mutator_flag = argv[3];
    std::transform(generic_mutator_flag.begin(), generic_mutator_flag.end(), generic_mutator_flag.begin(), ::tolower); //convert to lower case
    double probability = 0.0;
    bool argProvided = false;

    //Check if argument was provided
    if (argc == 5) {
      probability = atof(argv[4]);
      argProvided = true;
    }
    //Check probability is within bounds [0.0, 1.0]
    if (!(probability >= 0.0 && probability <= 1.0)) {
      cerr << "Provided probability argument is out of bounds. Must be within [0.0, 1.0]." << endl;
      exit(1);
    }

    if (generic_mutator_flag == "gf") {
      GenericFull gf;
      gf.mutate(inputFile, outputFile);
    }
    else if (generic_mutator_flag == "gfp") {
      if (!argProvided) {
        cerr << "Probability argument is missing." << endl;
        cerr << "Usage: " << argv[0] << " <input file> <output file> <generic mutator flag> <probability>" << endl;
        exit(1);
      }

      GenericFull gf;
      gf.mutate(inputFile, outputFile, probability);
    }
    else if (generic_mutator_flag == "g20") {
      Generic20 g20;
      g20.mutate(inputFile, outputFile);
    }
    else if (generic_mutator_flag == "g20p") {
      if (!argProvided) {
        cerr << "Probability argument is missing." << endl;
        cerr << "Usage: " << argv[0] << " <input file> <output file> <generic mutator flag> <probability>" << endl;
        exit(1);
      }

      Generic20 g20;
      g20.mutate(inputFile, outputFile, probability);
    }
    else if (generic_mutator_flag == "z") {
      //todo
    }
    else if (generic_mutator_flag == "zp") {
      //todo
    }
    else {
      cerr << "Provided generic mutator flag is not recognized." << endl;
      exit(1);
    }
  }
  //Otherwise, we will use mutators for supported file types
  else {

    //Ensure extensions is supported
    if (inputExt == "flv") {
      FLVFormat flvFile;
      flvFile.mutate(inputFile, outputFile);
    }
    else if (inputExt == "wav") {
      WAVFormat wavfile;
      wavfile.mutate(inputFile, outputFile);

    }
    else if (inputExt == "mid" || inputExt == "midi") {
      MIDIFormat midiFile;
      midiFile.mutate(inputFile, outputFile);
    }
    //Unsupported format
    else {
      cerr << "Provided file extention is not supported." << endl;
      exit(1);
    }
  }

  //Keep window alive in visual studio
#ifdef _DEBUG
    std::cin.get();
    std::cin.ignore();
#endif

  return 0;
}
