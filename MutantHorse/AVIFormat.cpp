#include "AVIFormat.h"

typedef struct {
      char dwFourCC[4],
      unsigned long dwSize
      unsigned char data[1]
} dChunk;
typedef struct {
      char dwList[4];
      unsigned long dwSize;
      char dwFourCC[4];
      dChunk data;
} dList;

namespace std {
      AVIFormat::AVIFormat() {
             fe = ifstream(iFile, ios::in | ios::binary);
             * isFound = false;

             char bid[4];
             unsigned long bSize;

             if(fe.is_open()) {
                   fe.seekg(0, fe.end);
                   int length = fe.tellg();
                   fe.seekg(0, fe.beg);

                   char * buffer = new char[length];

                   //
                   cout << length << endl;
                   //
             }


      }
      AVIFormat::mutate() {

      }
      AVIFormat::generate() {

      }
      AVIFormat::~AVIFormat() {
      }
}
