
OBJS = itty.o main.o

# directory where itty files live
export ITTY_DIR=$(PWD)/itty_core

# compile and link flags
export CFLAGS = -std=c99 -I$(ITTY_DIR)
export LDFLAGS = -L$(ITTY_DIR)
export LIBS = -litty_core

all: itty_core simpleserve benchmark 

# execution
.PHONY: run
run: simpleserve
	./examples/simpleserve/simpleserve	

# compilation
.PHONY:itty_core
itty_core:
	make -C itty_core itty_core

.PHONY:tests
tests: tests/CUnit itty_core
	make -C tests
	./tests/console_test

# examples
.PHONY: simpleserve
simpleserve:
	make -C examples/simpleserve simpleserve

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
benchmark: siege simpleserve
	./benchmark.sh

.PHONY:clean
clean:
	rm -rf ittybitty *.o siege siege.*
	make -C itty_core clean
	make -C tests clean
	make -C examples/simpleserve clean

