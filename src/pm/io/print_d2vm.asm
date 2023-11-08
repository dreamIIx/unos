%ifndef PRINT_D2VM
    %define PRINT_D2VM
%endif

[global asm_print_d2vm]

; Printing directly to video memory

[BITS 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

asm_print_d2vm:
    push ebp
    mov ebp, esp
    mov ebx, [esp + 2 * 4]
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
    popa
    mov esp, ebp
    pop ebp
    ret