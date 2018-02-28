ASM = nasm
FLAGS = -felf64

all: Dictionary

Dictionary: main.o lib.o dict.o
	ld -o $@ $^

%.o: %.asm
	$(ASM) $(FLAGS) $<

clean:
	rm -f *.o Dictionary

.PHONY: clean
