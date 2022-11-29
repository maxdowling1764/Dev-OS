[bits 16]
print_char:
    pusha
    mov ah, 0x0e
    mov al, bl
    int 0x10
    popa
    ret


; ebx - register to print hex
print_hex:
    pusha
    mov ah, 0x0e
    mov cx, 0

    hex_loop:
        mov dx, bx                      ; Copy bx into dx
        and dx, 0xF000                  ; Apply mask to 4 least significant bits
        shl bx, 4                       ; Shift bx left by 4
        shr dx, 12                      ; Shift remaining bits from far left to far right
        cmp dx, 9                       ; Check if letter or number
        jg is_letter                    ; Greater than 9, so it's a letter
        jmp is_number                   ; not greater than 9, so it's a number
        
        is_letter:
            add dx, 0x37                 ; ASCII offset for letters
            jmp hex_loop_end
        
        is_number:                      ; ASCII offset for numbers
            add dx, '0'
            jmp hex_loop_end
        
        hex_loop_end:
            mov al, dl                  ; Copy character to al
            int 0x10                    ; BIOS print char interrupt
            inc cx                      ; Increment counter
            cmp cx, 4                   ; Stop iteration when count is 4
            je print_hex_return

            jmp hex_loop                ; cx still less than 4, loop
    
    print_hex_return:
        popa
        ret
