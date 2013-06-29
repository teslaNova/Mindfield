include ../general.rules

C_SRCS=utils.c
OBJS=utils.o

.PHONY: all
	
%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@
	
all: $(OBJS)	
	
clean:
	$(RM) -f *.o
	