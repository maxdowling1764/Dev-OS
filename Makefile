include defs.mk
clean:
	rm bin/*
	rm obj/kernel/*

os-image: $(BIN_DIR)/boot.bin $(BIN_DIR)/kernel.bin
	cat $^ > $@

$(BOOT_BIN): $(BOOT_SRC)
	nasm -f bin -i $(SRC_DIR)/boot/ -o $@ $<

$(KERNEL_BIN): $(KERNEL_ENTRY_OBJ) $(KERNEL_C_OBJS)
	ld -melf_i386 -o $@ -Ttext 0x1003 $^ --oformat binary

$(OBJ_DIR)/kernel/%.o: $(SRC_DIR)/kernel/%.c
	gcc -m32 -fno-pie -ffreestanding -c $< -o $@

$(KERNEL_ENTRY_OBJ): $(KERNEL_ENTRY_SRC)
	nasm -f elf32 -i $(SRC_DIR)/kernel/ -o $@ $<


