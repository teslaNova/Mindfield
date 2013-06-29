global _k_init
extern _k_main

%define MB_MAGIC 0x1BADB002
%define MB_FLAGS 0x00000007 ; 1 -> page align, 2 -> memory info, 4 -> video mode info

section .text
  ; Multiboot Header Flags
  dd MB_MAGIC
  dd MB_FLAGS
  dd -(MB_MAGIC + MB_FLAGS)

  _k_init:
	mov esp, __k_stack
	add esp, 0xFFC
	
	push eax	; magic val
	push ebx	; multiboot header (see multiboot.h)
	
	call _k_main
	
	hlt
	
section .data
	__k_stack: times 0x1000 db 0
	