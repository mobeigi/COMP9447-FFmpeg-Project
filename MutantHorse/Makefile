CC= g++
CFLAGS= -c -std=c++11
CPP= IFReader.cpp AVIFormat.cpp FLVFormat.cpp
O= $(CPP:.cpp=.o)
E= main

all: $(O) $(E)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

$(E): $(O)
	$(CC) $? $@.cpp -o MutantHorse

clean:
	rm -f *.o MutantHorse
