include kernel/x86/x86.rules
include general.rules

x86-all:
	$(MAKE) -wC kernel/x86/kernel
	$(RM) -f ./boot/$(KRNL)
	$(CP) $(BIN)/x86/$(KRNL) ./boot/x86/boot/$(KRNL)
	$(MKISOFS) -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o $(BIN)/x86/$(KRNL).iso boot/x86
	 
x86-clean:
	$(RM) -f $(BIN)/x86/$(KRNL).iso
	$(MAKE) -wC kernel/x86/kernel clean
	
clean: x86_clean