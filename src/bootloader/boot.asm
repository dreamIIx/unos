[ORG 0x7c00]
[BITS 16]

main:
	mov ax, 0
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov [boot_drive], dl

	mov sp, 0x7c00
	mov si, os_boot_msg
	call print

	mov bx, 0x9000
	mov dh, 10
	mov dl, [boot_drive]
	call disk_load

	mov dx, [0x9000 + 512]
	mov si, dx
	call print					; TODO: implement print_hex, source=DX

	mov dx, [0x9000 + 1024]
	mov si, dx
	call print					; TODO: implement print_hex, source=DX

	jmp $

%ifndef PRINT
	%include "./src/misc/print.asm"
%endif

%ifndef READ_FLOPPY_DISK
	%include "./src/bootloader/read_floppy_disk.asm"
%endif

os_boot_msg:
	DB 'Hello world!', 0x0d, 0x0a, 0
boot_drive:
	DB 0

times 510-($-$$) DB 0
dw 0xaa55

times 512 DB 0
dw 'GL'
times 510 DB 0
dw 'HF'