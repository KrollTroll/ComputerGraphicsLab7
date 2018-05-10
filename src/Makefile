CC=g++
CFLAGS=-c -Wall
LDFLAGS= -lX11
SOURCES=draw.cpp line.cpp image.cpp point.cpp shape.cpp matrix.cpp drawing.cpp gcontext.cpp triangle.cpp x11context.cpp viewcontext.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=TransformImage

all: $(SOURCES) $(EXECUTABLE) 

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o: 
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) $< > $*.d

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.d
