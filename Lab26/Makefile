CC ?= gcc 
CFLAGS ?= -g -Wall -Werror

all: main.o deque.o
	${CC} -o main main.o deque.o

main.o: main.c 
	${CC} ${CFLAGS} -c main.c

deque.o: deque.c
	${CC} ${CFLAGS} -c deque.c

clean: 
	rm -rf *.o main
