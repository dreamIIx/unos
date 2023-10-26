%ifndef PRINT
    %define PRINT
%endif

[BITS 16]

print:
	pusha

print_loop:
	lodsb
	or al, al
	jz done_print
	mov ah, 0x0e
	mov bh, 0
	int 0x10
	jmp print_loop

done_print:
	popa
	ret