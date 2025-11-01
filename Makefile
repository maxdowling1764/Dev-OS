include defs.mk

WIN_USER_NAME := "$(shell cmd.exe /c "echo %USERNAME%")"
WSL_IMG_PATH := /mnt/c/Users/$(WIN_USER_NAME)/source/images
WIN_IMG_PATH := "C:\\Users\\$(WIN_USER_NAME)\\source\\images"
KERN_SIZE_FILE :=$(BIN_DIR)/kernel.size
run: install
	cmd.exe /c qemu-system-x86_64 $(WIN_IMG_PATH)\\os-image

install: os-image
	cp os-image $(WSL_IMG_PATH)

clean:
	rm bin/*
	rm obj/kernel/*

os-image: $(BOOT_BIN) $(KERNEL_BIN)
	cat $^ > $@

$(BOOT_BIN): $(BOOT_SRC) $(KERN_SIZE_FILE)
	size=$$(cat $(KERN_SIZE_FILE)); \
	nasm -f bin -dKERNEL_SECTORS=$$size -i $(SRC_DIR)/boot/ -o $@ $<

# Hack to make sure build of boot.bin is dependent on eval of 'stat -c%s bin/kernel.bin'
$(KERN_SIZE_FILE): $(KERNEL_BIN)
	size=$$(stat -c%s "$<"); \
	expr $$size / 512 + 1 > $@
	

$(KERNEL_BIN): $(KERNEL_ENTRY_OBJ) $(KERNEL_C_OBJS)
	ld -melf_i386 -o $@ -Tsrc/kernel/link.ld $^ --oformat binary

$(OBJ_DIR)/kernel/%.o: $(SRC_DIR)/kernel/%.c
	gcc -m32 -fno-pie -ffreestanding -c $< -o $@

$(KERNEL_ENTRY_OBJ): $(KERNEL_ENTRY_SRC)
	nasm -f elf32 -i $(SRC_DIR)/kernel/ -o $@ $<


