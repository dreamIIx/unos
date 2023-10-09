; Printing directly to video memory
[BITS 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_d2vm:
    pusha
    mov edx, VIDEO_MEMORY

print_d2vm_loop:
    mov al, [ebx]
    mov ah, WHITE_ON_BLACK

    test al, al
    jz print_d2vm_done

    mov [edx], ax

    add ebx, 1
    add edx, 2

    jmp print_d2vm_loop

print_d2vm_done:
    pops
    ret