include ../general.rules

C_SRCS=utils.c mm/pmm.c
OBJS=utils.o mm/pmm.o

.PHONY: all
	
%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@
	
all: $(OBJS)	
	
clean:
	$(RM) -f $(OBJS)
	