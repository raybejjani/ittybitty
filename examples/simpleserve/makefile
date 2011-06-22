
OBJS = $(subst .o,.c, $(shell ls *.c))

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
simpleserve: itty_core $(OBJS) content_matcher.rl.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) $(OBJS) -o $@ 

.PHONY:content_matcher.rl.c
content_matcher.rl.c: 
	../../tools/ittyfs.py static -o ./content_matcher.rl --template ../../tools/content_matcher.rl.tmpl
	ragel -C -G2 content_matcher.rl -o $@

.PHONY:itty_core
itty_core:
	make -C ../../itty_core itty_core

.PHONY:clean
clean:
	rm -rf simpleserve *.o content_matcher.rl*

