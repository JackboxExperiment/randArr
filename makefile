default: rand.o
	gcc rand.o

rand.o: rand.c
	gcc -c rand.c

run:
	./a.out

clean:
	rm -f *~ *.o *.out
