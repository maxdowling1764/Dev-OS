[org 0x7c00]
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl

mov bp, 0x9000
mov sp, bp

mov bx, msg
call print_str
call load_kernel
call switch_to_pm

jmp $

%include "print_str.asm"
%include "print_hex.asm"
%include "debug.asm"
%include "disk.asm"
%include "gdt.asm"
%include "print_str_pm.asm"
%include "protectedmode.asm"

[bits 16]
msg:
    db "Starting OS", 0

msg_pm:
    db "Entering PM", 0

msg_k:
    db "Loading Kernel", 0

msg_core_dump:
    db "Core Dump", 0
label_ax:
    db "disibpspbxdxcxax", 0

DISK_ERR_MSG:
    db "Error reading disk", 0

BOOT_DRIVE: db 0

load_kernel:
    mov bx, msg_k               ; Print Kernel Message
    call print_str

    mov bx, KERNEL_OFFSET       ; Instruct disk to load at address of KERNEL_OFFSET
    mov dh, 15                  ; Instruct disk to load 15 sectors 
    mov dl, [BOOT_DRIVE]        ; Instruct to load from disk 0
    call disk_load              ; Execute load
    ret

[bits 32]

begin_pm:
    call clear_screen_pm
    mov bx, msg_pm
    call print_str_pm
    call KERNEL_OFFSET
    jmp $

[bits 16]
times 510 - ($ - $$) db 0
dw 0xaa55
