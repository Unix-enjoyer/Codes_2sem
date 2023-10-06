CC ?= gcc 
CFLAGS ?= -g -Werror -pedantic
main: main.o mathparser.o
	${CC} -o main main.o mathparser.o

main.o: main.c 
	${CC} ${CFLAGS} -c main.c

functions.o: mathparser.c mathparser.o
	${CC} ${CFLAGS} -c mathparser.c

clean: 
	rm -rf *.o main
