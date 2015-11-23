CC= g++
CFLAGS= -c -O2 -fpermissive -std=c++11
CPP= FLVFormat.cpp g20.cpp gf.cpp IFReader.cpp MIDIFormat.cpp pad.cpp RandomMutator.cpp RandomOffsetMutator.cpp WAVFormat.cpp z.cpp
O= $(CPP:.cpp=.o)
E= main

all: $(O) $(E)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

$(E): $(O)
	$(CC) $? $@.cpp -o MutantHorse

clean:
	rm -f *.o MutantHorse
