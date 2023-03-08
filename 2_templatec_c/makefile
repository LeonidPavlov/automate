tmp=template
out=template.out

all : ${out}
	./${out} file

${out} : ${tmp}.o main.o
	gcc *.o -o ${out}

${tmp}.o : ${tmp}.c ${tmp}.h
	gcc -c ${tmp}.c

main.o : main.c ${tmp}.h
	gcc -c main.c

clear : 
	rm -f *.o
