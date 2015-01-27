CC=g++
CFLAGS=-c -Wall -std=c++0x -g
LDFLAGS=#-lstdc++
SOURCES=overhead.c main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=run

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ 
#	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE) 
	
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clear: 
	$(RM) $(EXECUTABLE) $(OBJECTS)

test:
	$(CC) test.cpp

