include ../../general.rules
include x86.rules

C_SRCS=main.c descriptor.c asm.c sse.c
ASM_SRCS=init.asm
OBJS=init.o $(C_SRCS:%.c=%.o)
OBJS_EXT=../mm/sm.o ../mm/pmm.o ../mm/malloc.o ../utils.o ../printf.o ../screen.o ../assert.o ../rtc.o ../itoa.o ../video/bga.o ../video/tm.o ../pci.o ../font.o ../ism.o ../cpu.o

.PHONY: all

all: $(OBJS)
	$(LD) $(LDFLAGS) -Map $(BIN_x86_MAP) -o $(BIN_x86_KRNL) $(OBJS) $(OBJS_EXT)

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.asm
	$(NASM) $(ASFLAGS) $^ -o $@
	
clean:
	$(RM) -f $(OBJS)