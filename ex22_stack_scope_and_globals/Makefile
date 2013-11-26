CC=cc
CFLAGS=-c -Wall -g
OBJECTS=ex22.o ex22_main.o
EXECUTABLE=ex22_main

all: clean $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $(realpath $<) -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

.PHONY: all clean
