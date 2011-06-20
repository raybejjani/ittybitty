
OBJS = itty.o main.o

export CFLAGS = -std=c99 -I$(PWD)/itty_core
export LDFLAGS = -L$(PWD)/itty_core/
export LIBS = -litty_core

all: ittybitty

# compilation
ittybitty: itty_core $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) $(OBJS) -o $@ 

.PHONY:itty_core
itty_core:
	make -C itty_core itty_core

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
	make -C itty_core clean
	make -C tests clean
