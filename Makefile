CC=gcc
CFLAGS=-Wall -Wextra -std=c99
TARGET=sigrh
SOURCES=main.c funciones.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET) *.dat *.o *~

test: $(TARGET)
	./$(TARGET)

.PHONY: all clean test