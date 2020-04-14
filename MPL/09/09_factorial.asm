%macro scall 4
           mov        rax,%1
           mov        rdi,%2
           mov        rsi,%3
           mov        rdx,%4
           syscall
%endmacro

section .data
           msg        : db " FACTORIAL OF NUMBER IS",0x0A
           len        : equ $-msg

section .bss
           fact       : resb 4
           cnt        : resb 4

section .text
           global     _start

_start:
           pop        rbx
           pop        rbx
           pop        rbx
           mov        cx,0
           mov        ax,01
           movzx      cx,byte[rbx]
           sub        cx,30h
           call       fact_proc
           call       htoa

           mov        rax,60
           mov        rdi,0
           syscall

;********PROCEDURE TO CALCULATE FACTORIAL********

fact_proc:
           cmp        cl,01h
           jne        do_calc
           mov        ax,1
           ret
           do_calc    :
           push       cx
           dec        cx
           call       fact_proc
           pop        cx
           mul        cl
           ret	

;************HEX TO ASCII PROCEDURE************

htoa:
           mov        rsi,fact
           mov        byte[cnt],4
up:
           rol        ax,4
           mov        bl,al
           and        bl,0x0F
           cmp        bl,09H
           jbe        next1
           add        bl,07H
next1:
           add        bl,30H
           mov        byte[rsi],bl
           inc        rsi
           dec        byte[cnt]
           jnz        up
           scall      1,1,fact,4
           ret