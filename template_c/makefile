test : dist/template.out
	dist/template.out 23_cocky_stuff ../..

dist/template.out : template.o test.o cocky_library.o
	gcc template.o test.o cocky_library.o -o dist/template.out

template.o : template.h template.c
	gcc -c template.c

cocky_library.o : lib/cocky_library.c lib/cocky_library.h
	gcc -c lib/cocky_library.c

test.o : test.c template.h
	gcc -c test.c

valgrind :
	valgrind dist/template.out 23_cocky_stuff ../..

clear :
	rm *.o dist/*.out
