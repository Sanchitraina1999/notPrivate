%macro scall 4
           mov        rax,%1
           mov        rdi,%2
           mov        rsi,%3
           mov        rdx,%4
           syscall
%endmacro

section .data
array : dd 102.56,104.25,235.26,205.04,36.01
arraycnt:dw 5
point : db '.'
meanmsg:db 0x0A,"Mean of the number is",0x0A
lenm: equ $-meanmsg
varmsg : db 0x0A,"Variance of the number are",0x0A
lenv: equ $-varmsg
stdmsg:db 0x0A,"standard deviation is",0x0A
len: equ $-stdmsg
hundred:dq 100
d: db 0x0A

section .bss
cnt :resb 2
cnt1 : resb 2
mean :resb 8
ans : resb 2
buffer:resb 10
variance : resb 4

section .text
global _start
_start:
           mov        rsi,array
           mov        byte[cnt],5
           finit
           fldz
up:
           fadd       dword[rsi]
           add        rsi,4
           dec        byte[cnt]
           jnz        up
           fidiv      word[arraycnt]
           fst        dword[mean]
           scall      1,1,meanmsg,lenm
           call       display

;**********VARIANCE OF THE NUMBER *******************
var:
           scall      1,1,varmsg,lenv
           mov        dword[variance],00
           fldz
           mov        rsi,array
           mov        byte[cnt],5
up3:
           fld        dword[rsi]
           fsub       dword[mean]
           fst        st1
           fmul       st0,st1
           fadd       dword[variance]
           fst        dword[variance]
           add        rsi,4
           dec        byte[cnt]
           jnz        up3
           fld        dword[variance]
           fidiv      word[arraycnt]
           fst        dword[variance]
           call       display
	
;***************** STANDARD DEVIATION ***************
stddev:
           scall      1,1,stdmsg,len
           fld        dword[variance]
           fsqrt
           call       display
           scall      1,1,d,1
           jmp        exit



;*********DISPLAY PROCESS FOR FLOATING  POINT  ************
display:
           fimul      dword[hundred] 
           fbstp      [buffer]
           mov        rsi,buffer+9
           mov        byte[cnt],9
up1:
	
           mov        al,byte[rsi]
           push       rsi
           call       htoa
	;scall 1,1,meanmsg,lenm
           pop        rsi
           dec        rsi
           dec        byte[cnt]
           jnz        up1
           scall      1,1,point,1
           mov        rsi,buffer
           mov        al,byte[rsi]
           call       htoa
           ret



;*********HEX TO ASCII *********************
htoa:
           mov        rdi,ans
           mov        byte[cnt1],2
up2:
           rol        al,4
           mov        bl,al
           and        bl,0x0F
           cmp        bl,9
           jbe        down1
           add        bl,7
down1:
           add        bl,30h
           mov        byte[rdi],bl
           inc        rdi
           dec        byte[cnt1]
           jnz        up2
           scall      1,1,ans,2
           ret
;****************EXIT**********************
exit:
           scall      60,0,0,0
