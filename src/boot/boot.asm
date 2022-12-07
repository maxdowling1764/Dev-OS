[org 0x7c00]
MMAP_OFFSET equ 0x1000
GDTPTR_OFFSET equ 0x1C02 
KERNEL_OFFSET equ 0x1C08

mov [BOOT_DRIVE], dl

mov bp, 0x9000
mov sp, bp

call load_kernel
mov ax, 0
mov es, ax
call init_mmap
call switch_to_pm

jmp $

%include "disk.asm"
%include "gdt.asm"
%include "mmap.asm"
%include "protectedmode.asm"

[bits 16]
BOOT_DRIVE: db 0

load_kernel:
    mov bx, KERNEL_OFFSET       ; Instruct disk to load at address of KERNEL_OFFSET
    mov dh, 18                  ; Instruct disk to load 15 sectors 
    mov dl, [BOOT_DRIVE]        ; Instruct to load from disk 0
    call disk_load              ; Execute load
    ret

[bits 32]

begin_pm:
    sgdt [GDTPTR_OFFSET]
    call KERNEL_OFFSET
    jmp $

[bits 16]
times 510 - ($ - $$) db 0
dw 0xaa55
