%macro myprintf 1
           mov         rdi,formatpf
           sub         rsp,8
           movsd       xmm0,[%1]
           mov         rax,1
           call        printf
           add         rsp,8
%endmacro

%macro myscanf 1
           mov         rdi,formatsf
           mov         rax,0
           sub         rsp,8
           mov         rsi,rsp
           call        scanf
           mov         r8,qword[rsp]
           mov         qword[%1],r8
           add         rsp,8
%endmacro

%macro scall 4
           mov         rax,%1
           mov         rdi,%2
           mov         rsi,%3
           mov         rdx,%4
           syscall
%endmacro

Section .data

eqn:	db "--------Quadratic equations------",0x0A 
        db "Enter the values of a, b, and c",0x0A
leneqn: equ $-eqn
four: dq 4
two: dq 2
formatpf: db "%lf",10,0
formatsf: db "%lf",0
ff1: db "%lf + i%lf",10,0
ff2: db "%lf - i%lf",10,0

rmsg: db 0x0A,"Roots are real. Roots: ",0x0A
rlen: equ $-rmsg
imsg: db 0x0A,"Roots are complex. Roots: ",0x0A
ilen: equ $-imsg


Section .bss
b2: resq 1
fourac: resq 1
twoa: resq 1
root1: resq 1
root2: resq 1
delta: resq 1
rdelta: resq 1

realn: resq 1
imag1: resq 1

a: resq 1
b: resq 1
c: resq 1


Section .text
extern printf
extern scanf

global main
main:

scall 1,1,eqn,leneqn

myscanf a
myscanf b
myscanf c
	
           finit
           fldz
	
           fld         qword[b]
           fmul        qword[b]
           fstp        qword[b2]                                 ;b^2
	
           fild        qword[four]
           fmul        qword[a]
           fmul        qword[c]
           fstp        qword[fourac]                             ;4ac
	
           fld         qword[b2]
           fsub        qword[fourac]
           fstp        qword[delta]                              ;b^2-4ac
		
           fild        qword[two]
           fmul        qword[a]
           fstp        qword[twoa]                               ;2a
	
           btr         qword[delta],63
	
           jc          imaginary
	
           scall       1,1,rmsg,rlen
	
           fld         qword[delta]
           fsqrt
           fstp        qword[rdelta]                             ;sqr_root(delta)
	
           fldz                                                  ;[-b+sqr_root(delta)]/2a
           fsub        qword[b]
           fadd        qword[rdelta]
           fdiv        qword[twoa]
           fstp        qword[root1]
           myprintf    root1
	
           fldz
           fsub        qword[b]
           fsub        qword[rdelta]
           fdiv        qword[twoa]
           fstp        qword[root2]
           myprintf    root2
	
           jmp         exit
	
imaginary: 

           scall       1,1,imsg,ilen
           fld         qword[delta]
           fsqrt
           fstp        qword[rdelta]
	
           fldz
           fsub        qword[b]
           fdiv        qword[twoa]
           fstp        qword[realn]                              ;real part
	
           fld         qword[rdelta]
           fdiv        qword[twoa]
           fstp        qword[imag1]                              ;imaginary part
				
mov rdi,   ff1
sub rsp,8
movsd xmm0,qword[realn]
movsd xmm1,qword[imag1]
mov rax,2
call printf
add rsp,8

mov rdi,ff2
sub rsp,8
movsd xmm0,qword[realn]
movsd xmm1,qword[imag1]
mov rax,2
call printf
add rsp,8

jmp exit

exit:
           mov         rax,60
           mov         rdi,0
           syscall			
