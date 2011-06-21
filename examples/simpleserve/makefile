
OBJS = itty.o main.o

# Expects:
#  ITTY_DIR: Directory where itty files and archives live

export CFLAGS = -std=c99 -I$(ITTY_DIR)
export LDFLAGS = -L$(ITTY_DIR)
export LIBS = -litty_core

all: simpleserve run

# execution
run: simpleserve
	./simpleserve

# compilation
simpleserve: itty_core $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) $(OBJS) -o $@ 

.PHONY:itty_core
itty_core:
	make -C ../../itty_core itty_core

.PHONY:clean
clean:
	rm -rf simpleserve *.o

