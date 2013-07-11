QEMU:
  apt-get? brew? emerge? ..?
  
  Ausführung in /mindfield/:
    qemu-system-i386 -cdrom bin/x86/mindfield.iso -d ioport,guest_errors,unimp,pcall -vga std -monitor stdio -m 256
    
    -vga std = Bochs Graphic Adapter (Bochs VBE Variante)
    -monitor stdio = QEMU Konsole (Informationen, On-the-fly Einstellungen, etc.)
    -d = Logflags
    -m = Speicher (In Megabyte)

Binutils (2.23):
  
  ./configure --program-prefix=i386-elf --target=i386-elf- --prefix=/usr/local --disable-nls CC=gcc-4.9
  
  make
  sudo make install

GCC (4.8.1):

  Voraussetzungen: GMP MPFR MPC

  ./configure --target=i386-elf --prefix=/usr/local --program-prefix=i386-elf- --disable-nls --enable-languages=c,c++ --without-headers CC=/usr/local/bin/gcc-4.9 CXX=/usr/local/bin/g++-4.9
	
  make all-gcc
  make all-target-libgcc
  sudo make install-gcc
  sudo make install-target-libgcc

Infos:
  
  CC/CXX ist nicht unbedingt nötig, da du dich nicht mit LLVM rumschlagen musst.
  
  Ansonsten lohnt ein Blick hier rein: http://wiki.osdev.org/GCC_Cross-Compiler
	
