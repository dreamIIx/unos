SOURCE_DIR = ./src
BUILD_DIR = ./build

BOOTLOADER_SOURCE_DIR = $(SOURCE_DIR)/bootloader
KERNEL_SOURCE_DIR = $(SOURCE_DIR)/kernel

BOOTLOADER_BUILD_DIR = $(BUILD_DIR)/bootloader
KERNEL_BUILD_DIR = $(BUILD_DIR)/kernel

BOOTLOADER_ASM = $(BOOTLOADER_SOURCE_DIR)/boot.asm
KERNEL_C = $(KERNEL_SOURCE_DIR)/main.c

BOOTLOADER_BIN = $(BOOTLOADER_BUILD_DIR)/bootloader.bin
KERNEL_O = $(KERNEL_SOURCE_DIR)/main.o
KERNEL_TMP = $(KERNEL_BUILD_DIR)/kernel.tmp
KERNEL_BIN = $(KERNEL_BUILD_DIR)/main.bin

FLOPPY_IMG = $(BUILD_DIR)/floppy.img

KERNEL_ENTRY_ADDRESS = 0x20200

ifeq ($(OS), Windows_NT)
	ASM = ${NASM_PATH}\nasm
	DD = ${CYGWIN_PATH}\bin\dd
	GCC = 
	MCOPY = 
	MKFS = 
	LD = 
	LD_M_OPT = 
	OBJCOPY = 
	OD = ${CYGWIN_PATH}\bin\od
	OD_OPT = -t x1 -A n
	RM = 
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Linux)
		ASM = nasm
		GCC = gcc
		DD = dd
		MCOPY = mcopy
		MKFS = mkfs
		LD = ld
		LD_M_OPT = elf_i386
		OBJCOPY = objcopy
		OBJCOPY_I_OPT = elf_i386
		OD = od
		OD_OPT = -t x1 -A n
		RM = rm
    endif
endif

$(info init..)

.PHONY: clean_boot build_boot floppy kernel bootloader

floppy: bootloader kernel $(FLOPPY_IMG)
kernel: $(KERNEL_BIN)
bootloader: $(BOOTLOADER_BIN)

$(FLOPPY_IMG): $(BOOTLOADER_BIN) $(KERNEL_BIN)
	$(info [MAKE] building: $@)
	$(DD) bs=512 count=2880 if=/dev/zero of=$@
#	$(MKFS) -t fat -F 12 -n "UNOS" $@
	$(DD) conv=notrunc if=$< of=$@
#	$(MCOPY) -i $@ $(word 2,$^) "::kernel.bin"
	$(DD) conv=notrunc seek=1 if=$(word 2,$^) of=$@

$(KERNEL_O): $(KERNEL_C)
	$(info [MAKE] building: $@)
	$(GCC) -fno-pie -ffreestanding -c $< -o $@
#	-m32

$(KERNEL_BIN): $(KERNEL_O)
	$(info [MAKE] building: $@)
	$(LD) -Ttext $(KERNEL_ENTRY_ADDRESS) --oformat binary $< -o $@
#	-m $(LD_M_OPT) $(KERNEL_TMP)
#	$(OBJCOPY) -I $(OBJCOPY_I_OPT) -O $(KERNEL_TMP) $< $@

$(BOOTLOADER_BIN): $(BOOTLOADER_ASM) ./src/rm/io/print.asm ./src/rm/io/print_hex.asm ./src/bootloader/read_floppy_disk.asm ./src/rm/misc/accumulate_sum.asm ./src/pm/switch2pm.asm
	$(info [MAKE] building: $@)
	$(ASM) -fbin $< -o $@
	$(OD) $(OD_OPT) $@

clean_boot:
	$(RM) -f $(FLOPPY_IMG)
	$(RM) -f $(KERNEL_O)
	$(RM) -f $(KERNEL_TMP)
	$(RM) -f $(KERNEL_BIN)
	$(RM) -f $(BOOTLOADER_BIN)
