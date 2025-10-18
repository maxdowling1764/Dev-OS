[bits 32]
[extern main]
call main
%include "idt.asm"
jmp $
