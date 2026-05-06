CC = cc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11
TARGET = connect_four

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

clean:
	rm -f $(TARGET)

.PHONY: all clean
