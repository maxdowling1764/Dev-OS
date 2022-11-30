[bits 32]
[global _start]
[extern main]
section .text
%include "idt.asm"
call main
jmp $
