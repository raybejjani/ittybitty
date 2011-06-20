# dispatch  builder.
# Inherits CC, CFLAGS if set

CFLAGS ?= -std=c99

OBJS = $(subst .c,.o,$(shell ls *.c))

itty_core: http_parser.c $(shell ls *.h) $(OBJS)
	$(AR) rcs lib$@.a $(OBJS)

http_parser.c: http_parser.rl $(shell ls *.h) 
	ragel -C -G2 $< -o $@


# util rules
.PHONY: viz
viz:
	ragel -G2 http_parser.rl -pV > foo.dot &&  dotty foo.dot && rm foo.dot

.PHONY:clean
clean:
	rm -rf *.o *.a
