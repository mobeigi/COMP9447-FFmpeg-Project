#ifndef __GContainerFormat__
#define __GContainerFormat__
namespace std {
      class GContainerFormat;
}

namespace std {
      class GContainerFormat {
      public:
            virtual void mutate() = 0;
            virtual void generate() = 0;
      };
}

#endif
