[org 0x7c00]

jmp $

%include "print_str.asm"
%include "print_hex.asm"
%include "debug.asm"
%include "disk.asm"

msg:
    db "Starting OS", 0

msg_core_dump:
    db "Core Dump", 0
label_ax:
    db "disibpspbxdxcxax", 0

DISK_ERR_MSG:
    db "Error reading disk", 0

BOOT_DRIVE: db 0

times 510 - ($ - $$) db 0
dw 0xaa55

times 256 dw 0xDADA
times 256 dw 0xDEAD
times 1024 dw 0x0000
