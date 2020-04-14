section .data
msg: db "MENU",0x0A
           db         "1.HEX to BCD ",0x0A
           db         "2.BCD to HEX ",0x0A
           db         "3.Exit",0x0A
len:equ $-msg
msgH: db "ENTER THE HEX NUMBER ",0x0A
lenH:equ $-msgH
msgB: db "ENTER THE BCD NUMBER ",0x0A
lenB:equ $-msgB
cnt: db 0
enter:db 0x0A

section .bss
	%macro scall 4
           mov        rax,%1
           mov        rdi,%2
           mov        rsi,%3
           mov        rdx,%4
           syscall
	%endmacro
choice: resb 2
num:resb 5
num1:resb 9
ans:resb 1
result:resb 5
factor:resb 5

section .text
global _start
_start:
           scall      1,1,msg,len
           scall      0,1,choice,2
           cmp        byte[choice],31h
           je         option1
           cmp        byte[choice],32h
           je         option2
           cmp        byte[choice],33h
           jae        exit
option1:

 ;******************HEX to BCD conversion******************

           scall      1,1,msgH,lenH
           scall      0,1,num,5
           call       atoh_16
           mov        bx,0x0A
           mov        byte[cnt],00
up:
           mov        dx,00
           div        bx
           push       dx
           inc        byte[cnt]
           cmp        ax,00
           jne        up
print:
           pop        ax
           cmp        ax,09h
           jbe        next2
           add        ax,07h
next2:
           add        ax,30h
           mov        byte[ans],al
           scall      1,1,ans,1	
           dec        byte[cnt]
           jnz        print
           scall      1,1,enter,1
           jmp        _start	

;*******************ASCII to HEX (4 digit no )***********************

atoh_16:
           mov        rsi,num
           mov        ax,00h
           mov        byte[cnt],04h
up1:       rol        ax,04
           mov        bl,byte[rsi]
           cmp        bl,39h
           jbe        next
           sub        bl,07h
next:
           sub        bl,30h
           add        al,bl
           inc        rsi
           dec        byte[cnt]
           jnz        up1
           ret

;*****************DISPLAY procedure*******************************

display:
           mov        rsi ,result+4
           mov        byte[cnt],5
calc:
	;ror bx,4
           mov        cl,00h
           mov        cl,bl
           and        cl,0x0F
           cmp        cl,09h
           jbe        next4
           add        cl,07h
next4:
           add        cl,30h
           mov        byte[rsi],cl
           ror        ebx,4
           dec        rsi
           dec        byte[cnt]
           jnz        calc
           scall      1,1,result,5
           ret


;**********************BCD to HEX *****************

option2:
           scall      1,1,msgB,lenB
           scall      0,1,num1,9
           mov        rsi,num1+7
           mov        byte[cnt],05
           mov        ebx,00h
	;clc
           mov        dword[factor],1
up4:
           mov        eax,0h
           mov        al,byte[rsi]
           sub        al,30h
           mul        dword[factor]
           add        ebx,eax
           mov        ax,0x0A
           mul        dword[factor]
           mov        dword[factor],eax
           dec        rsi
           dec        byte[cnt]
           jnz        up4
           call       display
           scall      1,1,enter,1
           jmp        _start	

;*******************EXIT**************************

exit:
           mov        rax,60
           mov        rdi,0
           syscall	