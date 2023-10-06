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

	mov [sum], bx
	popa
	ret

sum:
	DB 0