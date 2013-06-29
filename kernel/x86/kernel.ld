OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)
ENTRY(_k_init)

PHYS = 0x100000;

SECTIONS
{
	. = PHYS;
	_KERNEL_START = .;

	.text : AT(ADDR(.text)) {
		*(.text)
		*(.rodata*)

		. = ALIGN(4096);
	}

	.data : AT(ADDR(.data)) {
		*(.data)

		. = ALIGN(4096);
	}

	.bss : AT(ADDR(.bss)) {
		_sbss = .;
		*(COMMON)
		*(.bss)
		_ebss = .;
	}

	. = ALIGN(4096);

	_KERNEL_END = .;
	_KERNEL_SIZE = _KERNEL_END - _KERNEL_START;
}