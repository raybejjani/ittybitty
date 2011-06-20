# Test builder.
# Inherits CC, CFLAGS if set

CFLAGS ?= -std=c99

CFLAGS += -I$(PWD)/tests/CUnit/include/CUnit
LDFLAGS += -L$(PWD)/tests/CUnit/lib -lcunit

OBJS = $(subst .c,.o,$(shell ls *.c))


all: console_test

console_test: $(OBJS) $(shell ls *.h)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) $(OBJS) -o $@ 
	
.PHONY:clean
clean:
	rm -rf *.o console_test
