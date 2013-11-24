CC=cc
CFLAGS=-c -Wall -g
OBJECTS=object.o map.o monster.o room.o game.o
EXECUTABLE=game

all: clean game 

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

.PHONY: all clean
