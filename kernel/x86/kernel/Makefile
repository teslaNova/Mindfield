include ../x86.rules
include ../../../general.rules

C_SRCS=main.c
ASM_SRCS=init.asm
OBJS=init.o main.o ../../utils.o

.PHONY: all

all: $(OBJS)
	$(LD) $(LDFLAGS) -Map $(BIN_x86_MAP) -o $(BIN_x86_KRNL) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.asm
	$(NASM) $(ASFLAGS) $^ -o $@
	
clean:
	$(RM) -f *.o