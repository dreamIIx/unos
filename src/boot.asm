ORG 0x7C00
[BITS 16]

loop:
	jmp loop

times 510-($-$$) db 0

dw 0xaa55

