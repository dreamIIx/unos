[ORG 0x7c00]
[BITS 16]

KERNEL_OFFSET_ES equ 0x2020
KERNEL_OFFSET_BX equ 0

main:
	xor ax, ax
	mov ds, ax
	mov es, ax

	cli
	mov ss, ax
	mov sp, 0x7c00
	sti
	mov [boot_drive], dl

	mov si, os_boot_msg
	call print
	
	push ax
	push bx

	mov ax, KERNEL_OFFSET_ES
	mov es, ax
	mov bx, KERNEL_OFFSET_BX  
	mov dh, 15
	mov dl, [boot_drive]
	call disk_load
	
	pop bx
	pop ax

	mov si, KERNEL_OFFSET_ES
	xor cx, cx
	mov al, dh
	mov cx, 0x200
	mul cx
	mov cx, ax
	add cx, 0
	xor ah, ah
	call accumulate
 
	mov si, sum
	call print					; TODO: implement print_hex, source=?

	call switch_to_pm

%ifndef PRINT
	%include "./src/rm/io/print.asm"
%endif

%ifndef PRINT_HEX
	%include "./src/rm/io/print_hex.asm"
%endif

%ifndef READ_FLOPPY_DISK
	%include "./src/bootloader/read_floppy_disk.asm"
%endif

%ifndef ACCUMULATE_SUM
	%include "./src/rm/misc/accumulate_sum.asm"
%endif

boot_drive:
	DB 0
os_boot_msg:
	DB 'Hello world!', 0x0d, 0x0a, 0

%ifndef SWITCH_TO_PM
	%include "./src/pm/switch2pm.asm"
%endif

times 510-($-$$) DB 0
dw 0xaa55

;times 510 DB 0
;dw 0x3001
;dw 0x3001
;times 510 DB 0
;dw 0x0203
;times 510 DB 0
;dw 'GL'
;times 510 DB 0
;dw 'HF'
;times 510 DB 0

;times 456190 DB 1
;dw 'ye'