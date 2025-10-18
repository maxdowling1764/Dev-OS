SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
KERNEL_C_OBJS = $(patsubst %.c, %.o, $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(wildcard $(SRC_DIR)/kernel/*.c)))

BOOT_SRC = $(SRC_DIR)/boot/boot.asm
BOOT_BIN = $(BIN_DIR)/boot.bin
KERNEL_BIN = $(BIN_DIR)/kernel.bin

KERNEL_ENTRY_SRC = $(SRC_DIR)/kernel/kernel_entry.asm
KERNEL_ENTRY_OBJ = $(OBJ_DIR)/kernel/kernel_entry.o