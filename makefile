
OBJS = itty.o main.o

CFLAGS = -std=c99

export CFLAGS

all: ittybitty

# compliation
ittybitty: $(OBJS)
	$(CC) $(OBJS) -o $@

.PHONY:tests
tests: tests/CUnit
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
	make -C tests clean
