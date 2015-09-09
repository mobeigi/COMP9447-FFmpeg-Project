#ifndef __GContainerFormat__
#define __GContainerFormat__
namespace std {
      class GContainerFormat;
}

namespace std {
      class GContainerFormat {
      public:
            virtual ~GContainerFormat() {}
            virtual void mutate() = 0;
            virtual void generate() = 0;
            void SetInputFile(string i) {
                  iFile = m;
            }
            voud SetOutputFile(string o) {
                  oFile = m;
            }
      protected:
            string iFile;
            string oFile;
            bool * isFound;
      };
}

#endif __GContainerFormat__
