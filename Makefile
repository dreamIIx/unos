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
	ASM = ${NASM_PATH}\nasm
	DD = ${CYGWIN_PATH}\bin\dd
	MCOPY = 
	MKFS = 
	LD = 
	OD = ${CYGWIN_PATH}\bin\od
	OD_OPT = -t x1 -A n
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Linux)
		ASM = nasm
		DD = dd
		MCOPY = mcopy
		MKFS = mkfs
		LD = ld
		OD = od
		OD_OPT = -t x1 -A n
    endif
endif

$(info init..)

.PHONY: clean_boot build_boot

floppy: bootloader kernel $(FLOPPY_IMG)
kernel: $(KERNEL_BIN)
bootloader: $(BOOTLOADER_BIN)

$(FLOPPY_IMG): $(BOOTLOADER_BIN) $(KERNEL_BIN)
	$(info [MAKE] building: $@)
	$(DD) bs=512 count=2880 if=/dev/zero of=$@
#	$(MKFS) -t fat -F 12 -n "UNOS" $@
	$(DD) conv=notrunc if=$< of=$@
#	$(MCOPY) -i $@ $(word 2,$^) "::kernel.bin"

$(KERNEL_BIN): $(KERNEL_ASM)
	$(info [MAKE] building: $@)
	$(ASM) -fbin $< -o $@

$(BOOTLOADER_BIN): $(BOOTLOADER_ASM)
	$(info [MAKE] building: $@)
	$(ASM) -fbin $< -o $@
	$(OD) $(OD_OPT) $@

clean_boot:
	rm $(FLOPPY_IMG)
	rm $(KERNEL_BIN)
	rm $(BOOTLOADER_BIN)
