#include "FLVFormat.h"
#include "RandomMutator.h"
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

    size_t readBytes = ifreader.read(flvheader.data(), flvheader.size());

    //Write FLV header
    ofs.write((char *)flvheader.data(), readBytes);

    //Read Metadata Packet Header (15 Bytes)
    vector<unsigned char> metadataPacket(15);

    readBytes = ifreader.read(metadataPacket.data(), metadataPacket.size());

    //Write Metadata Packet Header
    ofs.write((char *)metadataPacket.data(), readBytes);

    //Get payload size
    size_t metadataPayloadSize = 0;
    for (int i = 5; i < 8; ++i) { //bytes at index 5-7 (3 bytes) contain payload size, big endian
      metadataPayloadSize = (metadataPayloadSize << 8) + (metadataPacket[i]);
    }

    //Read metadata payload (payloadSize Bytes)
    vector<unsigned char> metadataPayload(metadataPayloadSize);

    readBytes = ifreader.read(metadataPayload.data(), metadataPayload.size());

    //Write metadata payload
    ofs.write((char *)metadataPayload.data(), readBytes);

    //For the remainder of the flv file
    //Look at each packet
    //Then write header as is while mutating the payload (data)
    while (readBytes != 0) {

      //Read packet header (15 bytes)
      vector<unsigned char> packet(15);

      readBytes = ifreader.read(packet.data(), packet.size());

      //Write Metadata Packet Header
      ofs.write((char *)packet.data(), readBytes);

      if (readBytes < 15) continue;   //if not a full header, this means 4 bytes remain (size of previous packet fields)

      //Get payload size
      size_t packetPayloadSize = 0;

      for (int i = 5; i < 8; ++i) { //bytes at index 5-7 (3 bytes) contain payload size, big endian
        packetPayloadSize = (packetPayloadSize << 8) + (packet[i]);
      }

      //Read packet payload
      vector<unsigned char> packetPayload(packetPayloadSize);

      readBytes = ifreader.read(packetPayload.data(), packetPayload.size());
      if (readBytes == 0) break;

      //Temp mutation of payload
      for (auto it = packetPayload.begin(); it != packetPayload.end(); ++it) {
        *it = rand() % 256;
      }

      //Write metadata payload
      ofs.write((char *)packetPayload.data(), readBytes);
    }

  }

  void FLVFormat::generate() {
    //Todo
  }
}
