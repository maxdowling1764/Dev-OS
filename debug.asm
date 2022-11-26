coredump:
    pusha
    push sp
    
    mov bx, msg_core_dump
    call print_str
    call print_new_line

    mov cx, 0
    coredump_loop:

        mov bx, label_ax
        add bx, cx
        mov dx, bx              ; initialize terminating value
        
        add dx, 2               ; offset by 2
        call print_substr       ; print substring
        
        mov bx, '='
        call print_char
        
        mov bx, [esp+ecx+2]
        call print_hex
        call print_new_line

        add cx, 2
        cmp cx, 16

        jne coredump_loop
    pop ax
    popa
    ret