exec = make_ramdisk.out
sources = $(wildcard *.c)
objects = $(sources:.c=.o)
flags = -g -Wall -lm -ldl -fPIC -rdynamic

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c
	gcc -c $(flags) $< -o $@

clean:
	-rm *.out
	-rm *.o
