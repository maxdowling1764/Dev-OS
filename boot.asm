[org 0x7c00]

mov bx, msg
call print_str
call print_new_line

mov ax, 0xFF42
mov cx, 0xAABC
mov bx, 0xAABB
call coredump

jmp $

%include "print_str.asm"
%include "print_hex.asm"
%include "debug.asm"
msg:
    db "Starting OS", 0

msg_core_dump:
    db "Core Dump", 0
label_ax:
    db "disibpspbxdxcxax", 0

times 510 - ($ - $$) db 0
dw 0xaa55