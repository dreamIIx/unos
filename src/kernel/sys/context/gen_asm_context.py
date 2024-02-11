exceptions_with_error_code = {8, 10, 11, 12, 13, 14, 17, 21, 29, 30}

with open("./src/kernel/sys/context/tramplinsWContext.asm", "w") as f:


    wr = f.write
    wr("[BITS 32]\n\n")
    
    for i in range(0, 256):
        wr(f"[GLOBAL tramplin_{str(hex(i))[2:]}]\n")

    wr('''
collect_context:
    push ds
    push es
    push fs
    push gs
    pusha
''')

    wr("\n\n")
    for i in range(0, 256):
        wr(f"tramplin_{str(hex(i))[2:]}:\n")
        if i not in exceptions_with_error_code:
            wr("\tpush 0x0\n")
        wr(f"\tpush 0x{str(hex(i))[2:]}\n")
        wr("\tjmp collect_context")
        wr("\n\n")