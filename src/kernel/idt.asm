[global _idt_load]
[extern _p_idt]
_idt_load:
    lidt [_p_idt]
    ret

%macro ISR_NO_ERR 1
    [global _isr%1]
    _isr%1:
        push byte 0
        push byte %1
        jmp isr_comm
%endmacro

%macro ISR_ERR 1
    [global _isr%1]
    _isr%1:
        cli
        push byte %1
        jmp isr_comm
%endmacro

%macro IRQ 2
    [global _isr%1]
    _isr%1:
        cli
        push byte 0
        push byte %2
        jmp isr_comm
%endmacro

%macro 
[extern _isr_handler]
[extern _fault_handler]

%assign i 0
%rep 8
    ISR_NO_ERR i
%assign i i+1
%endrep

ISR_ERR 8
ISR_NO_ERR 9

%assign i 10
%rep 5
    ISR_ERR i
%assign i i + 1
%endrep

%rep 17
    ISR_NO_ERR i
%assign i i + 1
%endrep

%assign i 0
%assign j 32
%rep 15
    IRQ i j
%assign i i + 1
%assign j j + 1
%endrep

isr_comm:
    pusha
    
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov eax, esp
    push eax
    call _isr_handler
    
    pop eax
    pop gs
    pop fs
    pop es
    pop ds 
    popa
    add esp 8
    sti
    iret

[extern _irq_handler]

irq_comm:
    pusha
    push ds
    push es
    push fs
    push gs
    
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov eax, esp
    push eax
    call _irq_handler

    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp 8
    sti
    iret
