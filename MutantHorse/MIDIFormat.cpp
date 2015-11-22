#include "MIDIFormat.h"
#include "RandomMutator.h"
#include "RandomOffsetMutator.h"
#include <vector>


namespace std {
  void MIDIFormat::mutate(const string input, const string output)
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

    //Read MIDI header
    vector<unsigned char> midiheader(14);
    size_t readBytes = ifreader.read(midiheader.data(), midiheader.size());

    //Write MIDI header
    ofs.write((char *)midiheader.data(), readBytes);

    //Extract the number of tracks in the midi (stored in big endian)
    size_t numTracks = (midiheader[10] << 8) + (midiheader[11]); 

    // Process and mutate each track
    for (int trackIndex = 0; trackIndex < numTracks; trackIndex++) {
        //Read the track header
	vector<unsigned char> trackheader(8);
	readBytes = ifreader.read(trackheader.data(), trackheader.size());

	//Exit if nothing is read
	if (readBytes == 0) break;
	
	//Write the track header
	ofs.write((char *)trackheader.data(), readBytes);

	//Determine the length of the track data
	size_t dataLength = 0;
	for (int i = 4; i <= 7; i++) {
	    dataLength = (dataLength << 8) + (trackheader[i]);
	}

	//Prepare a mutator
	RandomMutator randomMutator;

	//Read the track data, and mutate it
	vector<unsigned char> trackdata(dataLength);
	readBytes = ifreader.read(trackdata.data(), trackdata.size());

	for (auto it = trackdata.begin(); it != trackdata.end(); ++it) {
	    *it = randomMutator.mutate(*it);
	}

	//Write the mutated data
	ofs.write((char *)trackdata.data(),readBytes);
    }
  }
}
