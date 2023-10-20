%ifndef READ_AFLOPPY_DISKS
    %define READ_AFLOPPY_DISKS
%endif

[BITS 16]

disk_load:
    mov ax, 0x0
    mov ds, ax

    mov ah, 0x02    ; 0x2 - read sectors from drive
    mov al, 1       ; read DH sector
    mov ch, 0x00    ; select cylinder 0
    mov dh, 0x00    ; select head 0
    mov cl, 0x01    ; select sector 1 (512B each sector, so it follows out boot sector)
                    ; now read w/bootloader
                    
loop_load:
    int 0x13
    jc disk_error

    mov ah, 0x02    ; 0x2 - read sectors from drive

    push ax
    mov ax, es
    add ax, 0x20
    mov es, ax

    add cl, 0x1

    cmp cl, 19     ; == 0x12
    jne continue
    mov ax, 65472
    and cx, ax

    mov cl, 1

    cmp dh, 0x1
    xor dh, 0x1
    jne continue

    add ch, 1

continue:
    mov ax, ds
    add ax, 0x1
    cmp ax, 768
    mov ds, ax
    
    pop ax
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