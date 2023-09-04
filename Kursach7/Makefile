CC ?= gcc 
CFLAGS ?= -g -Werror -pedantic
main: main.o vector.o
	${CC} -o main main.o vector.o

main.o: main.c 
	${CC} ${CFLAGS} -c main.c

functions.o: vector.c vector.o
	${CC} ${CFLAGS} -c vector.c

clean: 
	rm -rf *.o main