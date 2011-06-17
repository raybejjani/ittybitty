

all: server

server: *.c
	$(CC) main.c -o server

.PHONY:clean
clean:
	rm -f server *.o
