init_mmap:
    pusha
    mov di, MMAP_OFFSET + 2      ; location of mmap starts at n_mmap + offset of 2 bytes for n_mmap 
    xor ebx, ebx
    xor bp, bp
    mov edx, 0x0534D4150    ; "SMAP" -> edx
    
    mov eax, 0xe820         ; e820 memory map routine
    mov [es:di + 20], dword 1
    mov ecx, 24
    int 0x15
    jc .failed
    
    mov edx, 0x0534D4150
    cmp eax, edx
    jne .failed

    test ebx, ebx
    je .failed
    jmp .loop_init

    .loop:
        mov eax, 0xe820
        mov [es:di + 20], dword 1
        mov ecx, 24
        int 0x15                    ; Read 24 bytes from e820
        jc .done                    ; Finished if carry flag is set
        mov edx, 0x0534D4150        ; Restore edx trashed by e820
    
    .loop_init:
        jcxz .next                  ; cx is n bytes returned by e820, skip if zero bytes returned
        cmp cl, 20                  ; check if we got extended (>20) address map
        jbe .not_ext                ; Not extended
        test byte [es:di + 20], 1   ; Check if ignore flag is set
        je .next                    ; skip if ignored
    
    .not_ext:
        mov ecx, [es:di + 8]        ; get low 32 bits of entry length
        or ecx, [es:di + 12]
        jz .next                    ; Skip if both hi and low bits of entry length are zero
        inc bp                      ; increment entry count
        add di, 24                  ; Move to next entry location

    .next:
        test ebx, ebx
        jne .loop                   ; Break loop if continuation value is 0

    .done:
        mov [MMAP_OFFSET], bp            ; Store final count of entries in n_mmap
        clc                         ; Clear carry
        popa
        ret

    .failed:
        popa
        ret
