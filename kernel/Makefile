include ../general.rules

C_SRCS=utils.c mm/pmm.c printf.c screen.c
OBJS=utils.o mm/pmm.o printf.o screen.o

.PHONY: all
	
%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@
	
all: $(OBJS)	
	
clean:
	$(RM) -f $(OBJS)
	