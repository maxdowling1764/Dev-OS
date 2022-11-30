[bits 32]
[extern _main]
call _main
%include "idt.asm"

jmp $
