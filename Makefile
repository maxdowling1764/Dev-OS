include defs.mk
clean:
	rm bin/*
	rm obj/kernel/*

os-image: $(BIN_DIR)/boot.bin $(BIN_DIR)/kernel.bin
	cat $^ > $@

$(BIN_DIR)/boot.bin: $(SRC_DIR)/boot/boot.asm
	nasm -f bin -i $(SRC_DIR)/boot/ -o $@ $<

$(BIN_DIR)/kernel.bin: $(OBJ_DIR)/kernel/kernel_entry.o $(OBJ_DIR)/kernel/kernel.o $(OBJ_DIR)/kernel/common.o $(OBJ_DIR)/kernel/monitor.o $(OBJ_DIR)/kernel/irq.o $(OBJ_DIR)/kernel/idt.o $(OBJ_DIR)/kernel/isr.o
	ld -melf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

$(OBJ_DIR)/kernel/idt.o: $(SRC_DIR)/kernel/idt.c
	gcc -m32 -fno-pie -ffreestanding -c $< -o $@

$(OBJ_DIR)/kernel/isr.o: $(SRC_DIR)/kernel/isr.c
	gcc -m32 -fno-pie -ffreestanding -c $< -o $@

$(OBJ_DIR)/kernel/irq.o: $(SRC_DIR)/kernel/irq.c
	gcc -m32 -fno-pie -ffreestanding -c $< -o $@

$(OBJ_DIR)/kernel/monitor.o: $(SRC_DIR)/kernel/monitor.c
	gcc -m32 -fno-pie -ffreestanding -c $< -o $@

$(OBJ_DIR)/kernel/common.o: $(SRC_DIR)/kernel/common.c
	gcc -m32 -fno-pie -ffreestanding -c $< -o $@

$(OBJ_DIR)/kernel/kernel.o: $(SRC_DIR)/kernel/kernel.c
	gcc -m32 -fno-pie -ffreestanding -c $< -o $@

$(OBJ_DIR)/kernel/kernel_entry.o: $(SRC_DIR)/kernel/kernel_entry.asm
	nasm -f elf32 -i $(SRC_DIR)/kernel/ -o $@ $<


