all : compile
	# ../dist/template_C.out

compile : template.o main.o
	gcc template.o main.o -o ../dist/template_C.out

template.o : template.c template.h
	gcc -c template.c

main.o : main.c template.h
	gcc -c main.c

clear : 
	rm -f *.o

