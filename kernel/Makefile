include ../general.rules

C_SRCS=utils.c mm/pmm.c mm/malloc.c printf.c screen.c assert.c
OBJS=utils.o mm/pmm.o mm/malloc.o printf.o screen.o assert.o

.PHONY: all
	
%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@
	
all: $(OBJS)	
	
clean:
	$(RM) -f $(OBJS)
	