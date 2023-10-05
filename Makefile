SOURCE_DIR = ./src
BUILD_DIR = ./build

BOOTLOADER_SOURCE_DIR = $(SOURCE_DIR)/bootloader
KERNEL_SOURCE_DIR = $(SOURCE_DIR)/kernel

BOOTLOADER_BUILD_DIR = $(BUILD_DIR)/bootloader
KERNEL_BUILD_DIR = $(BUILD_DIR)/kernel

BOOTLOADER_ASM = $(BOOTLOADER_SOURCE_DIR)/boot.asm
KERNEL_ASM = $(KERNEL_SOURCE_DIR)/main.asm

BOOTLOADER_BIN = $(BOOTLOADER_BUILD_DIR)/bootloader.bin
KERNEL_BIN = $(KERNEL_BUILD_DIR)/kernel.bin

FLOPPY_IMG = $(BUILD_DIR)/floppy.img

ifeq ($(OS), Windows_NT)
	ASM = 
	DD = 
	LD = 
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Linux)
		ASM = nasm
		DD = dd
		LD = ld
		OD = od
		ASM_OPT = -fbin
		OD_OPT = -t x1 -A n
    endif
endif

$(info init..)

.PHONY: clean_boot build_boot

floppy: $(FLOPPY_IMG)
kernel: $(KERNEL_BIN)
bootloader: $(BOOTLOADER_BIN)

$(FLOPPY_IMG): $(BOOTLOADER_BIN)
	$(info )
	$(info building: $@)
	$(DD) bs=1024 count=1440 if=/dev/zero of=$@
	$(DD) conv=notrunc if=$< of=$@

$(BOOTLOADER_BIN): $(BOOTLOADER_ASM)
	$(info )
	$(info building: $@)
	$(ASM) $(ASM_OPT) $< -o $@
	$(OD) $(OD_OPT) $@

clean_boot:
	rm $(FLOPPY_IMG)
	rm $(KERNEL_BIN)
	rm $(BOOTLOADER_BIN)