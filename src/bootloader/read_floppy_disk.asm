%ifndef READ_AFLOPPY_DISKS
    %define READ_AFLOPPY_DISKS
%endif

[BITS 16]

disk_load:
    mov di, 0x0

    mov ch, 0x00    ; select cylinder 0
    mov dh, 0x00    ; select head 0
    mov cl, 0x01    ; select sector 1 (512B each sector, so it follows out boot sector)
                    ; now read w/bootloader
                    
loop_load:
    mov ah, 0x02    ; 0x2 - read sectors from drive
    mov al, 1       ; read DH sector
    int 0x13
    jc disk_error

    mov ax, es
    add ax, 0x20
    mov es, ax

    add cl, 0x1

    cmp cl, 0x13
    jl continue

    and cx, 0xffc0
    add cl, 1

    xor dh, 0x1
    jne continue

    add ch, 1

continue:
    add di, 0x1
    cmp di, 768
    
    jne loop_load
    ret

disk_error:
    mov si, disk_error_msg
    call print
    jmp $

%ifndef PRINT
    %include "./src/misc/print.asm"
%endif

disk_error_msg:
    DB 'Disk read error!', 0x0d, 0x0a, 0