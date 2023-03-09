test : dist/test.out
	dist/test.out

dist/test.out : template.o test.o cocky_library.o
	gcc template.o test.o cocky_library.o -o dist/test.out

template.o : template.h template.c
	gcc -c template.c

cocky_library.o : lib/cocky_library.c lib/cocky_library.h
	gcc -c lib/cocky_library.c

test.o : test.c template.h
	gcc -c test.c

valgrind :
	valgrind dist/test.out

clear :
	rm *.o dist/*.out
