CC = gcc
CFLAGS = -Wall -pedantic-errors -Werror -ggdb
LD = gcc

all: linkedlist

linkedlist: main.o linkedlist.o
	$(LD) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.txt *.bin linkedlist

.PHONY: clean
