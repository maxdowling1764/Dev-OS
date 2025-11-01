include defs.mk

WIN_USER_NAME := "$(shell cmd.exe /c "echo %USERNAME%")"
WSL_IMG_PATH := /mnt/c/Users/$(WIN_USER_NAME)/source/images
WIN_IMG_PATH := "C:\\Users\\$(WIN_USER_NAME)\\source\\images"
KERN_SIZE := $(shell expr \( $$(stat -c%s $(KERNEL_BIN)) / 512 \) + 1) 
run: install
	cmd.exe /c qemu-system-x86_64 $(WIN_IMG_PATH)\\os-image

install: os-image
	cp os-image $(WSL_IMG_PATH)

clean:
	rm bin/*
	rm obj/kernel/*

os-image: $(BIN_DIR)/boot.bin $(BIN_DIR)/kernel.bin
	cat $^ > $@

$(BOOT_BIN): $(BOOT_SRC) $(KERNEL_BIN)
	nasm -f bin -d KERNEL_SECTORS=$(KERN_SIZE) -i $(SRC_DIR)/boot/ -o $@ $<

$(KERNEL_BIN): $(KERNEL_ENTRY_OBJ) $(KERNEL_C_OBJS)
	ld -melf_i386 -o $@ -Tsrc/kernel/link.ld $^ --oformat binary

$(OBJ_DIR)/kernel/%.o: $(SRC_DIR)/kernel/%.c
	gcc -m32 -fno-pie -ffreestanding -c $< -o $@

$(KERNEL_ENTRY_OBJ): $(KERNEL_ENTRY_SRC)
	nasm -f elf32 -i $(SRC_DIR)/kernel/ -o $@ $<


