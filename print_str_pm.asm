[bits 32]

VIDEO_MEM equ 0xb8000
WOB equ 0x0f

clear_screen_pm:
    pusha
    mov edx, VIDEO_MEM
    mov al, 0
    mov ah, WOB

    cls_row_loop:
        mov [edx], ax
        add edx, 2
        cmp edx, VIDEO_MEM + 2000
        jne cls_row_loop

    popa
    ret

print_str_pm:
    pusha
    mov edx, VIDEO_MEM

    print_str_pm_loop:
        mov al, [ebx]
        mov ah, WOB

        cmp al, 0
        je print_str_pm_done
        
        mov [edx], ax

        add ebx, 1
        add edx, 2

        jmp print_str_pm_loop

    print_str_pm_done:
        popa
        ret