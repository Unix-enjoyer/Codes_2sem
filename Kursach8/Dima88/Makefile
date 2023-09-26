CC ?= gcc 
CFLAGS ?= -g -Wall -Werror

all: main.o dlinkedList.o
	${CC} -o main main.o dlinkedList.o

main.o: main.c 
	${CC} ${CFLAGS} -c main.c

dlinkedList.o: dlinkedList.c
	${CC} ${CFLAGS} -c dlinkedList.c

clean: 
	rm -rf *.o main