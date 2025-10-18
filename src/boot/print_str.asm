[bits 16]
print_str:
    pusha
    mov ah, 0x0e        ; BIOS scrolling tele-type routine

    print_str_loop:
        mov al, [bx]
        cmp al, 0
        je print_str_return

        int 0x10
        inc bx
        jmp print_str_loop
    
    print_str_return:
        popa
        ret

print_substr:
    pusha
    mov ah, 0x0e

    print_substr_loop:
        mov al, [bx]
        cmp bx, dx
        je print_substr_return

        int 0x10
        inc bx
        jmp print_substr_loop
        
    print_substr_return:
        popa
        ret

print_new_line:
    pusha
    mov ah, 0x0e

    mov al, 0xD
    int 0x10

    mov al, 0xA
    int 0x10
    popa
    ret