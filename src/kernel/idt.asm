[extern fault_handler]
[extern irq_handler]
[global idt_load]
[extern p_idt]
idt_load:
    lidt [p_idt]
    ret

%macro ISR_NO_ERR 1
    [global isr%1]
    isr%1:
        push byte 0
        push byte %1
        jmp isr_comm
%endmacro

%macro ISR_ERR 1
    [global isr%1]
    isr%1:
        cli
        push byte %1
        jmp isr_comm
%endmacro

%macro IRQ 2
    [global irq%1]
    irq%1:
        cli
        push byte 0
        push byte %2
        jmp irq_comm
%endmacro

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
%rep 16
    IRQ i, j
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
    call fault_handler
    
    pop eax
    pop gs
    pop fs
    pop es
    pop ds 
    popa
    add esp, 8
    sti
    iret

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
    mov eax, irq_handler
    call eax

    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    sti
    iret
