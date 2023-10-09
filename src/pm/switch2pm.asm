%ifndef SWITCH_TO_PM
    %define SWITCH_TO_PM
%endif

; Switch to protected mode

%ifndef GDT
	%include "./src/pm/gdt.asm"
%endif

%ifndef PRINT_D2VM
	%include "./src/pm/io/print_d2vm.asm"
%endif

[BITS 16]

switch_to_pm:
    cli
    lgdt [gdt_descriptor]
    
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    jmp CODE_SEG:init_pm

[BITS 32]

init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x20000
    mov esp, ebp

    call begin_pm

begin_pm:
	mov ebx, msg_pm_begin
	call print_d2vm
	jmp $

msg_pm_begin db "Hello from 32-bit protected mode!", 0