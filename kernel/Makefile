include ../general.rules

C_SRCS=utils.c mm/pmm.c mm/malloc.c printf.c screen.c assert.c rtc.c itoa.c
OBJS=$(C_SRCS:%.c:%.o)

.PHONY: all
	
%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@
	
all: $(OBJS)	
	
clean:
	$(RM) -f $(OBJS)
	