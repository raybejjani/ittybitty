
OBJS = itty.o main.o

CFLAGS = -std=c99

all: ittybitty

# compliation
ittybitty: $(OBJS)
	$(CC) $(OBJS) -o $@

#util
siege-2.70: siege-2.70.tar.gz
	tar -xf siege-2.70.tar.gz
siege: siege-2.70
	mkdir -p siege/etc
	(cd siege-2.70 && \
		./configure --prefix=`pwd`/../siege && \
		make && make install\
	)
# setup
benchmark: siege ittybitty
	./benchmark.sh

.PHONY:clean
clean:
	rm -rf ittybitty *.o siege siege.*
