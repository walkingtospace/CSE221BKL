CC=g++
CFLAGS=-c -Wall -std=c++0x -g -O0
LDFLAGS=#-lstdc++
SOURCES=rpi_pmu.c network_roundtrip_client.c
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

