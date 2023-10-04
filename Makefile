SOURCE_DIR = ./src
BUILD_DIR = ./build
BOOT_ASM = $(SOURCE_DIR)/boot.asm
BOOT_BIN = $(BUILD_DIR)/boot.bin
BOOT_IMG = $(BUILD_DIR)/boot.img

ifeq ($(OS), Windows_NT)
	ASM = 
	DD = 
	LD = 
	BOOT = $(BOOT_IMG)
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Linux)
		ASM = nasm
		DD = dd
		LD = ld
		OD = od
		ASM_OPT = -fbin
		OD_OPT = -t x1 -A n 
		BOOT = $(BOOT_IMG)
    endif
endif

$(info init..)

.PHONY: clean_boot build_boot
build_boot: $(BOOT)

$(BOOT_BIN): $(BOOT_ASM)
	$(info )
	$(info processing (stage 1))
	$(ASM) $(ASM_OPT) $< -o $@
	$(OD) $(OD_OPT) $@

$(BOOT): $(BOOT_BIN)
	$(info )
	$(info processing  (stage 2))
	$(DD) bs=1024 count=1440 if=/dev/zero of=$@
	$(DD) conv=notrunc if=$< of=$@

clean_boot:
	rm $(BOOT_BIN)