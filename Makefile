SOURCE_DIR = ./src
BUILD_DIR = ./build

BOOTLOADER_SOURCE_DIR = $(SOURCE_DIR)/bootloader
KERNEL_SOURCE_DIR = $(SOURCE_DIR)/kernel

BOOTLOADER_BUILD_DIR = $(BUILD_DIR)/bootloader
KERNEL_BUILD_DIR = $(BUILD_DIR)/kernel

BOOTLOADER_ASM = $(BOOTLOADER_SOURCE_DIR)/boot.asm
KERNEL_C = $(KERNEL_SOURCE_DIR)/kernel.c
KERNEL_ENTRY_ASM = $(KERNEL_SOURCE_DIR)/kernel_entry.asm

BOOTLOADER_BIN = $(BOOTLOADER_BUILD_DIR)/bootloader.bin
KERNEL_O = $(KERNEL_BUILD_DIR)/kernel.o
KERNEL_ENTRY_O = $(KERNEL_BUILD_DIR)/kernel_entry.o
KERNEL_TMP = $(KERNEL_BUILD_DIR)/kernel.tmp
KERNEL_BIN = $(KERNEL_BUILD_DIR)/kernel.bin

FLOPPY_IMG = $(BUILD_DIR)/floppy.img

KERNEL_ENTRY_ADDRESS = 0x20200

ifeq ($(OS), Windows_NT)
	ASM = ${NASM_PATH}\nasm
	DD = ${CYGWIN_PATH}\bin\dd
	GCC = gcc
	MCOPY = 
	MKFS = 
	LD = ld
	LD_M_OPT = i386pe
	OBJCOPY = objcopy
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
		OBJCOPY = objcopy
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

$(BUILD_DIR)/pm/io/print_d2vm.o: $(SOURCE_DIR)/pm/io/print_d2vm.asm
	$(info [MAKE] building: $@)
	$(ASM) -f elf $< -o $@

$(KERNEL_BUILD_DIR)/sys/io/printf.o: $(KERNEL_SOURCE_DIR)/sys/io/printf.c							\
	$(KERNEL_SOURCE_DIR)/sys/io/printf.h
	$(info [MAKE] building: $@)
	$(GCC) -Wall -m32 -mno-sse -fno-pie -ffreestanding -nostdlib -fno-stack-protector -c $< -o $@

$(KERNEL_BUILD_DIR)/sys/memory/mem_utils.o: $(KERNEL_SOURCE_DIR)/sys/memory/mem_utils.c				\
	$(KERNEL_SOURCE_DIR)/sys/memory/mem_utils.h
	$(info [MAKE] building: $@)
	$(GCC) -Wall -m32 -mno-sse -fno-pie -ffreestanding -nostdlib -fno-stack-protector -c $< -o $@

$(KERNEL_BUILD_DIR)/sys/memory/alloc.o: $(KERNEL_SOURCE_DIR)/sys/memory/alloc.c				\
	$(KERNEL_SOURCE_DIR)/sys/memory/alloc.h
	$(info [MAKE] building: $@)
	$(GCC) -Wall -m32 -mno-sse -fno-pie -ffreestanding -nostdlib -fno-stack-protector -c $< -o $@

$(KERNEL_BUILD_DIR)/sys/interruption.o: $(KERNEL_SOURCE_DIR)/sys/interruption.c				\
	$(KERNEL_SOURCE_DIR)/sys/idt.h
	$(info [MAKE] building: $@)
	$(GCC) -Wall -m32 -mno-sse -fno-pie -ffreestanding -nostdlib -fno-stack-protector -c $< -o $@

$(KERNEL_ENTRY_O): $(KERNEL_ENTRY_ASM)
	$(info [MAKE] building: $@)
	$(ASM) -f elf $< -o $@

$(KERNEL_O): $(KERNEL_C)																	\
	$(KERNEL_SOURCE_DIR)/sys/io/io.h $(KERNEL_SOURCE_DIR)/sys/memory/memory.h
	$(info [MAKE] building: $@)
	$(GCC) -Wall -m32 -mno-sse -fno-pie -ffreestanding -nostdlib -fno-stack-protector -c $< -o $@
#	-m32

$(KERNEL_BIN): $(KERNEL_ENTRY_O) $(BUILD_DIR)/pm/io/print_d2vm.o $(KERNEL_O)												\
	$(KERNEL_BUILD_DIR)/sys/memory/mem_utils.o $(KERNEL_BUILD_DIR)/sys/io/printf.o					
	$(info [MAKE] building: $@)
	$(LD) -m i386pe -Ttext $(KERNEL_ENTRY_ADDRESS) $^ -o $(KERNEL_TMP)
#	$(KERNEL_TMP)
	$(OBJCOPY) -I pe-i386 -O binary $(KERNEL_TMP) $@

$(BOOTLOADER_BIN): $(BOOTLOADER_ASM) $(SOURCE_DIR)/rm/io/print.asm							\
	$(SOURCE_DIR)/bootloader/read_floppy_disk.asm $(SOURCE_DIR)/pm/switch2pm.asm			\
	$(SOURCE_DIR)/pm/gdt.asm $(SOURCE_DIR)/pm/io/print_d2vm.asm								
	$(info [MAKE] building: $@)
	$(ASM) -fbin $< -o $@
	$(OD) $(OD_OPT) $@

$(FLOPPY_IMG): $(BOOTLOADER_BIN) $(KERNEL_BIN)
	$(info [MAKE] building: $@)
	$(DD) bs=512 count=2880 if=/dev/zero of=$@
#	$(MKFS) -t fat -F 12 -n "UNOS" $@
	$(DD) conv=notrunc if=$< of=$@
#	$(MCOPY) -i $@ $(word 2,$^) "::kernel.bin"
	$(DD) conv=notrunc seek=1 if=$(word 2,$^) of=$@

clean_boot:
#	$(info [MAKE] do  $@:)
#	$(RM) -f $(FLOPPY_IMG)
#	$(RM) -f $(KERNEL_ENTRY_O)
#	$(RM) -f $(KERNEL_O)
#	$(RM) -f $(KERNEL_TMP)
#	$(RM) -f $(KERNEL_BIN)
#	$(RM) -f $(BOOTLOADER_BIN)
#	$(RM) -f $(BOOTLOADER_BIN)
