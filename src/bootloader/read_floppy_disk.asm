%ifndef READ_FLOPPY_DISK
    %define READ_FLOPPY_DISK
%endif

ORG 0x7c00
BITS 16

disk_load:
    push dx

    mov ah, 0x02
    mov al, dh      ; read DH sector
    mov ch, 0x00    ; select cylinder 0
    mov dh, 0x00    ; select head 0
    mov cl, 0x02    ; select sector 2 (512B each sector, so it follows out boot sector)

    int 0x13

    jc disk_error

    pop dx
    cmp dh, al
    jne disk_error
    ret

disk_error:
    mov bx, disk_error_msg
    call print
    jmp $

%ifndef PRINT
    %include "./src/misc/print.asm"
%endif

disk_error_msg:
    DB 'Disk read error!', 0x0d, 0x0a, 0