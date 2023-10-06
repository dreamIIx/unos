[ORG 0x7c00]
[BITS 16]

main:
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov [boot_drive], dl

	mov sp, 0x7c00
	mov si, os_boot_msg
	call print

	mov bx, 0x9000
	mov dh, 5
	mov dl, [boot_drive]
	call disk_load

	call accumulate

	mov si, 0x9000 + 1024 + 512
	call print					; TODO: implement print_hex, source=?

	mov si, 0x9000  + 1024 + 1024
	call print					; TODO: implement print_hex, source=?

	jmp $

accumulate:
	pusha
	xor bx, bx
	mov si, 0x9000

	xor cx, cx
	mov al, dh
	mov cx, 0x200
	mul cx
	mov cx, ax
	add cx, 0x9000
	xor ah, ah
accumulate_loop:
	lodsb
	add bx, ax
	cmp si, cx
	jl accumulate_loop

	mov [sum], bx
	mov si, sum
	xchg bx, bx
	call print					; TODO: implement print_hex, source=?
	popa
	ret

%ifndef PRINT
	%include "./src/misc/print.asm"
%endif

%ifndef PRINT_HEX
	%include "./src/misc/print_hex.asm"
%endif

%ifndef READ_FLOPPY_DISK
	%include "./src/bootloader/read_floppy_disk.asm"
%endif

os_boot_msg:
	DB 'Hello world!', 0x0d, 0x0a, 0
boot_drive:
	DB 0
sum:
	DB 0

times 510-($-$$) DB 0
dw 0xaa55

times 512 DB 0
dw 0x3001
times 510 DB 0
dw 0x0203
times 510 DB 0
dw 'GL'
times 510 DB 0
dw 'HF'
times 510 DB 0