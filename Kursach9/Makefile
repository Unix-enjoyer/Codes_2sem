CC ?= gcc 
CFLAGS ?= -g -Wall -Werror

all: main.o table.o
	${CC} -o main main.o table.o

main.o: main.c 
	${CC} ${CFLAGS} -c main.c

table.o: table.c
	${CC} ${CFLAGS} -c table.c

clean: 
	rm -rf *.o main