#include "AVIFormat.h"

typedef struct {
      char dwFourCC[4];
      unsigned long dwSize;
      unsigned char data[1];
} dChunk;
typedef struct {
      char dwList[4];
      unsigned long dwSize;
      char dwFourCC[4];
      dChunk data;
} dList;

namespace std {
      AVIFormat::AVIFormat() {
      }
      void AVIFormat::mutate() {

      }
      void AVIFormat::generate() {
      }
}
