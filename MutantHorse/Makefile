CC= g++
CFLAGS= -c -std=c++11
CPP= IFReader.cpp GContainerFormat.cpp AVIFormat.cpp
O= $(CPP:.cpp=.o)
E= main

all: $(O) $(E)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

$(E): $(O)
	$(CC) $(O) $(E).cpp -o $@

clean:
	rm -f *.o $(E)
