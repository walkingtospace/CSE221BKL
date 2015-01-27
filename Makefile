CC=g++
CFLAGS=-c -Wall -std=c++0x -g
LDFLAGS=#-lstdc++
SOURCES=
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=run

#all: $(SOURCES) $(EXECUTABLE)
#	./run 

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ 
	
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clear: 
	$(RM) $(EXECUTABLE) $(OBJECTS)

test:
	$(CC) test.cpp

