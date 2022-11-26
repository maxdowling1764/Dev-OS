coredump:
    pusha
    
    mov bx, msg_core_dump
    call print_str
    call print_new_line

    mov cx, 0
    coredump_loop:

        ; This block prints 2 consecutive chars in label_ax
        ; label_ax stores the labels of each register printed in coredump
        mov bx, label_ax        ; Initialize start of substring
        add bx, cx              ; Offset start of substring by current iteration
        mov dx, bx              ; initialize end of substring
        
        add dx, 2               ; offset end of substring by 2 to get 2 chars
        call print_substr       ; print substring
        
        ; Separate register label from value
        mov bx, '='
        call print_char
        
        mov bx, [esp+ecx]
        call print_hex
        call print_new_line

        add cx, 2
        cmp cx, 16

        jne coredump_loop
    popa
    ret