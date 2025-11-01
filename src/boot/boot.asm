[org 0x7c00]
MMAP_OFFSET equ 0x08000
GDTPTR_OFFSET equ 0x08C02 
KERNEL_OFFSET equ 0x08C08

mov [BOOT_DRIVE], dl

mov ax, 0x9000
mov ss, ax
mov bp, 0xFFFF
mov sp, bp

call load_kernel
mov ax, 0x0
mov es, ax          ; Load e820 mmap to segment at GDT[1] (Kernel data)
call init_mmap
call switch_to_pm

jmp $

%include "disk.asm"
%include "gdt.asm"
%include "mmap.asm"
%include "protectedmode.asm"

[bits 16]
BOOT_DRIVE: db 0

%ifndef KERNEL_SECTORS
%define KERNEL_SECTORS 15
%endif

load_kernel:
    mov ax, 0x0
    mov es, ax
    mov bx, 0x8c08       ; Instruct disk to load at address of KERNEL_OFFSET
    mov dh, KERNEL_SECTORS                  ; Instruct disk to load 15 sectors 
    mov dl, [BOOT_DRIVE]        ; Instruct to load from disk 0
    call disk_load              ; Execute load
    ret

[bits 32]

begin_pm:
    sgdt [GDTPTR_OFFSET]
    jmp CODE_SEG:KERNEL_OFFSET
    jmp $

[bits 16]
times 510 - ($ - $$) db 0
dw 0xaa55
