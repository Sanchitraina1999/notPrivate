section .data
msg : db "***MENU****",0x0A
           db         "1.Successive addition",0x0A
           db         "2.Shift and Add method",0x0A
           db         "3.Exit",0x0A
lmsg : equ $-msg

m1:db "ENTER THE FIRST NUMBER (16 digits): ",0x0A
l1:equ $-m1
m2:db "ENTER THE SECOND NUMBER (16 digits): ",0x0A
l2:equ $-m2
m3:db "ANSWER IS = ",0x0A
l3:equ $-m3

cnt:db 00
enter : db 0x0A

section .bss
choice:resb 2
num1: resb 20
num2: resb 20
temp: resb 20
result: resb 20
	%macro scall 4
           mov        rax,%1
           mov        rdi,%2
           mov        rsi,%3
           mov        rdx,%4
           syscall
	%endmacro

section .text
global _start
_start:
           scall      1,1,msg,lmsg
           scall      0,1,choice,2
           cmp        byte[choice],33h
           jae        exit

           scall      1,1,m1,l1
           scall      0,1,temp,17
           call       atoh16
           mov        qword[num1],rax    
	
           scall      1,1,m2,l2
           scall      0,1,temp,17
           call       atoh16
           mov        qword[num2],rax

           cmp        byte[choice],31h
           je         option1
           cmp        byte[choice],32h
           je         option2

;*****************SUCCESSIVE ADDITION METHOD *********************

option1:
           mov        rbx,qword[num1]
           mov        rcx,qword[num2]
           mov        rax,0                            ;initialize rax to store answer..
	
           cmp        rcx,0h                           ;check the multiplication with 0
           je         skip3
loop1:
           add        rax,rbx
           loop       loop1
skip3:
           mov        rbx,rax
           scall      1,1,m3,l3
           mov        rax,rbx
           call       display
           scall      1,1,enter,1
           jmp        _start

;*********************ADD and SHIFT METHOD*************************

option2:
           mov        rbx,qword[num1]
           mov        rdx,qword[num2]
           mov        cl,64
;(16 digit * 4 bit per digit = 64 bit )
           mov        rax,0                            ;rax to store the result
loop2:
           shl        rax,1
           rol        rbx,1
           jnc        skip
           add        rax,rdx
skip:
           loop       loop2
           mov        rbx,rax
           scall      1,1,m3,l3
           mov        rax,rbx
           call       display
           scall      1,1,enter,1
           jmp        _start

exit:
           mov        rax,60
           mov        rdi,0
           syscall




;***********************ASCII TO HEX***************************

atoh16:
           mov        rsi,temp
           mov        rbx,0
           mov        byte[cnt],0x10
           mov        rax,00
up:
           rol        rax,4
           mov        bl,byte[rsi]
           cmp        bl,39h
           jbe        next
           sub        bl,07
next:
           sub        bl,30h
           add        rax,rbx
           inc        rsi
           dec        byte[cnt]
           jnz        up
           ret

;**************************DISPLAY***************************

display:
           mov        rsi,result
           mov        byte[cnt],16
up2:
           rol        rax,4
           mov        bl,al
           and        bl,0x0F
           cmp        bl,09h
           jbe        next2
           add        bl,07h
next2:
           add        bl,30h
           mov        byte[rsi],bl
           inc        rsi
           dec        byte[cnt]
           jnz        up2
           scall      1,1,result,16
           ret

