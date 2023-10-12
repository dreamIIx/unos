%ifndef READ_AFLOPPY_DISKS
    %define READ_AFLOPPY_DISKS
%endif

[BITS 16]

disk_load:
    xor cx, cx

    mov ah, 0x02    ; 0x2 - read sectors from drive
    mov al, 1      ; read DH sector
    mov ch, 0x00    ; select cylinder 0
    mov dh, 0x00    ; select head 0
    mov cl, 0x02    ; select sector 2 (512B each sector, so it follows out boot sector)

loop_load:
    int 0x13
    jc disk_error

    mov ah, 0x02    ; 0x2 - read sectors from drive


    push ax
    mov ax, es
    add ax, 0x20
    mov es, ax
    pop ax

    add [iter_counter], byte 0x1

    cmp [iter_counter], byte 18
    jne continue
    mov [iter_counter], byte 0

    push ax
    mov ax, 65472
    and cx, ax
    pop ax

    cmp dh, 0x1
    xor dh, 0x1
    jne continue

    add ch, 1

continue:
    add cx, 0x1
    add [sector_counter], word 0x1
    cmp [sector_counter], word 896
    jne loop_load
    xchg bx, bx
    ret

iter_counter:
    db 1
sector_counter:
    dw 0

disk_error:
    mov si, disk_error_msg
    call print
    jmp $

%ifndef PRINT
    %include "./src/misc/print.asm"
%endif

disk_error_msg:
    DB 'Disk read error!', 0x0d, 0x0a, 0