CC ?= gcc 
CFLAGS ?= -g -Werror -pedantic

main: main.o vector.o sparse_matrix.o
	${CC} -o main main.o vector.o sparse_matrix.o

main.o: main.c 
	${CC} ${CFLAGS} -c main.c

functions.o: vector.c vector.o sparse_matrix.c sparse_matrix.o
	${CC} ${CFLAGS} -c vector.c sparse_matrix.c

clean: 
	rm -rf *.o main