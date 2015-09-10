#include "FLVFormat.h"

#include <vector>

namespace std {
  void FLVFormat::mutate(const string input, const string output)
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

    //Read FLV header
    vector<unsigned char> flvheader(9);

    size_t readBytes = ifreader.read(flvheader.size(), flvheader.data());

    //Write FLV header
    ofs.write((char *)flvheader.data(), flvheader.size());

    //Read Metadata Packet Header (15 Bytes)
    vector<unsigned char> metadataPacket(15);

    readBytes = ifreader.read(metadataPacket.size(), metadataPacket.data());

    //Write Metadata Packet Header
    ofs.write((char *)metadataPacket.data(), metadataPacket.size());

    //Get payload size
    size_t payloadSize = 0;
    for (int i = 5; i < 8; ++i) { //bytes at index 5-7 (3 bytes) contain payload size, big endian
      payloadSize = (payloadSize << 8) + (metadataPacket[i] & 0xFF);
    }

    //Read metadata payload (payloadSize Bytes)
    vector<unsigned char> metadataPayload(payloadSize);

    readBytes = ifreader.read(metadataPayload.size(), metadataPayload.data());

    //Write metadata payload
    ofs.write((char *)metadataPayload.data(), metadataPayload.size());

    //For the remainder of the flv file
    //Look at each packet
    //Then write header as is while mutating the payload (data)

  }

  void FLVFormat::generate() {
    //Todo
  }
}
