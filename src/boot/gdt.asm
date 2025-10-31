gdt_start: 
gdt_null:
    dd 0x0
    dd 0x0

gdt_code:
    ; Limit: 20 bits
    ; Base : 32 bits
    ; Flags: 12 bits
    ; sizeof(gdt_entry) = 64 bits
    dw 0xffff		; Limit (lower 2 bytes)
    dw 0x0		; Base (lower 2 bytes)
    db 0x0		; Base (byte 3)
    db 10011010b	; Access Flags
    db 11001111b	; Flags, Limit (upper nibble)
    db 0x0		; Base (byte 4)

gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
