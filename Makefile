include general.rules

x86-all:
	$(MAKE) -wC kernel all ARCH=x86
	$(MAKE) -wC kernel/x86 all ARCH=x86
	$(RM) -f ./boot/$(KRNL)
	$(CP) $(BIN)/x86/$(KRNL) ./boot/x86/boot/$(KRNL)
	$(MKISOFS) -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o $(BIN)/x86/$(KRNL).iso boot/x86
	 
x86-clean:
	$(RM) -f $(BIN)/x86/$(KRNL).iso
	$(MAKE) -wC kernel clean
	$(MAKE) -wC kernel/x86 clean
	
clean: x86-clean