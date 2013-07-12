include ../general.rules

C_SRCS=utils.c mm/sm.c mm/pmm.c mm/malloc.c printf.c screen.c assert.c rtc.c itoa.c video/bga.c video/tm.c pci.c font.c ism.c cpu.c
OBJS=$(C_SRCS:%.c=%.o)

ifeq ($(ARCH),x86)
	CFLAGS += -DARCH_X86
endif

.PHONY: all
	
all: $(OBJS)
	
%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@	
	
clean:
	$(RM) -f $(OBJS)
	