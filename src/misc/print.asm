%ifndef PRINT
    %define PRINT
%endif

ORG 0x7c00
BITS 16

print:
	push si
	push ax
	push bx

print_loop:
	lodsb
	or al, al
	jz done_print
	mov ah, 0x0e
	mov bh, 0
	int 0x10
	jmp print_loop

done_print:
	pop bx
	pop ax
	pop si
	ret