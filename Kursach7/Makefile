CC ?= gcc 
CFLAGS ?= -g -Werror -pedantic
main: main.o sparse_matrix.o
	${CC} -o main main.o sparse_matrix.o

main.o: main.c 
	${CC} ${CFLAGS} -c main.c

functions.o: sparse_matrix.c vector.o
	${CC} ${CFLAGS} -c sparse_matrix.c

clean: 
	rm -rf *.o main