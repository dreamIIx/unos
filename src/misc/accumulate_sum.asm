%ifndef ACCUMULATE_SUM
    %define ACCUMULATE_SUM
%endif

[BITS 16]

accumulate:
	pusha
	xor bx, bx

accumulate_loop:
	lodsb
	add bx, ax
	cmp si, cx
	jl accumulate_loop

	xchg bx, bx
	mov [sum], bx
	popa
	ret

sum:
	DW 0
null_byte:
	DB 0