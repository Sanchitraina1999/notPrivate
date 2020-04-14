%macro scall 4
           mov        rax,%1
           mov        rdi,%2
           mov        rsi,%3
           mov        rdx,%4
           syscall
%endmacro

section .data

msg1:db "content of GDTR are:"
len1:equ $-msg1

msg2:db "limit of GDTR is:"
len2:equ $-msg2

msg3:db "content of LDTR are:"
len3:equ $-msg3

msg4:db "content of IDTR are:"
len4:equ $-msg4

msg5:db "limit of IDTR is:"
len5:equ $-msg5

msg6:db "content of TR is:"
len6:equ $-msg6

msg7:db "content of MSW are:"
len7:equ $-msg7

msg8:db "Working in real mode"
len8:equ $-msg8

msg9:db "Working in protected mode"
len9:equ $-msg9

enter:db 0x0A
cnt:db 0

section .bss

msw:resb 4
res:resb 4
gdt:resb 6
idt:resb 6

section .text

global _start
_start:

smsw eax

BT eax,0
jnc down

scall 1,1,msg9,len9
scall 1,1,enter,1
jmp next

down:
scall 1,1,msg8,len8

next:
scall 1,1,msg7,len7
smsw eax
mov dword[msw],eax
mov rsi,msw+2
mov ax,word[rsi]
call htoa

mov rsi,msw
mov ax,word[rsi]
call htoa

scall 1,1,enter,1

scall 1,1,msg3,len3
sldt ax

call htoa
scall 1,1,enter,1

scall 1,1,msg6,len6
str ax
call htoa
scall 1,1,enter,1

sgdt [gdt]
scall 1,1,msg1,len1
mov rsi,gdt+4
mov ax,word[rsi]
call htoa
mov rsi,gdt+2
mov ax,word[rsi]
call htoa
scall 1,1,enter,1

scall 1,1,msg2,len2
mov rsi,gdt
mov ax,word[rsi]
call htoa
scall 1,1,enter,1

sidt [idt]
scall 1,1,msg4,len4
mov rsi,idt+4
mov ax,word[rsi]
call htoa
mov rsi,idt+2
mov ax,word[rsi]
call htoa
scall 1,1,enter,1

scall 1,1,msg5,len5
mov rsi,idt
mov ax,word[rsi]
call htoa
scall 1,1,enter,1


jmp exit

htoa:

mov rdi,res
mov byte[cnt],4

up:
rol ax,4
mov bl,al
and bl,0x0F
cmp bl,09
jbe next2
add bl,07h
next2:
add bl,30h
mov byte[rdi],bl
inc rdi
dec byte[cnt]
jnz up

scall 1,1,res,4
ret

exit:
    mov rax,60
    mov rdi,0
    syscall
