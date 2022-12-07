[bits 16]
disk_load:
    push dx

    mov ah, 0x02
    mov al, dh
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02

    int 0x13

    jc disk_err

    pop dx
    cmp dh, al
    jne disk_err
    
    ret

disk_err:
    jmp $
