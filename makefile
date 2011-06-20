
OBJS = itty.o main.o

export CFLAGS = -std=c99 -I$(PWD)/http_dispatch
export LDFLAGS = -L$(PWD)/http_dispatch/
export LIBS = -lhttp_dispatch

all: ittybitty

# compilation
ittybitty: http_dispatch $(OBJS)
	$(CC) $(OBJS) -o $@

.PHONY:http_dispatch
http_dispatch:
	make -C http_dispatch http_dispatch

.PHONY:tests
tests: tests/CUnit ittybitty
	make -C tests

#util
siege-2.70: siege-2.70.tar.gz
	tar -xf siege-2.70.tar.gz
siege: siege-2.70
	mkdir -p siege/etc
	(cd siege-2.70 && \
		./configure --prefix=`pwd`/../siege && \
		make && make install\
	)

tests/CUnit: CUnit-2.1-2-src.tar.bz2
	tar -xf CUnit-2.1-2-src.tar.bz2
	mkdir -p tests/CUnit
	(cd CUnit-2.1-2 && \
		./configure --prefix=`pwd`/../tests/CUnit && \
		make && make install\
	)
# setup
benchmark: siege ittybitty
	./benchmark.sh

.PHONY:clean
clean:
	rm -rf ittybitty *.o siege siege.*
	make -C http_dispatch clean
	make -C tests clean
