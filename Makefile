CC=gcc

SOURCES= quicksort.c heapsort.c simulator.c

all: quicksort heapsort

quicksort: quicksort.c simulator.c
	gcc -o quicksort quicksort.c simulator.c

heapsort: heapsort.c simulator.c
	gcc -o heapsort heapsort.c simulator.c

clean:
	-rm -f *.o quicksort heapsort

run:
	./quicksort ./heapsort
