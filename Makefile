CC=g++
CFLAGS=-Wall
BIN=out.exe
SOURCES=*.cpp

$(BIN):	
	$(CC) $(CFLAGS) $(SOURCES) -o $(BIN)

clean:
	rm *.exe *.o

