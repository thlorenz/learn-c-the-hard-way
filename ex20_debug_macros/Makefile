CC=cc
CFLAGS=-c -Wall -g
OBJECTS=ex20.o
EXECUTABLE=ex20

all: clean $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@

.c.o:
	$(CC) $(CFLAGS) -c $(realpath $<)  -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

.PHONY: all clean
