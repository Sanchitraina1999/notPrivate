%macro print 2
mov rax,1
mov rdi,1
mov rsi,%1
mov rdx,%2
Syscall
%endmacro

%macro read 2
mov rax,0
mov rdi,1
mov rsi,%1
mov rdx,%2
Syscall
%endmacro

section .data

    menu:   db "-----Menu-----",0x0A
            db      "1.Non-overlapping without string",0x0A
            db      "2.Non-ovrelapping with string",0x0A
            db      "3.Overlapping without string",0x0A
            db      "4.Overlapping with string",0x0A
            db      "5.exit",0x0A
    lenmenu: equ $-menu

    array: dq 0x94326702319234A2,0xAD76342598301249,0x34618902315670C4,0x9874632015429ECD,0x754230120AB389C7
    new1: dq 0x00,0x00,0x00,0x00,0x00

    count: db 0
    count2: db 0
    count3: db 0
    count4: db 0
    count5: db 0

    msg: db "non-overlapping without string",0x0A
    len: equ $-msg
    msga: db "non-overlapping with string",0x0A
    lena: equ $-msga
    msgb: db "overlapping without string",0x0A
    lenb: equ $-msgb
    msgn: db "overlapping with string",0x0A
    lenn: equ $-msgn


    msg2: db "intitial",0x0A
    len2: equ $-msg2
    msg3: db "final",0x0A
    len3: equ $-msg3
    msgr: db "Invalid",0x0A
    lenr: equ $-msgr

    a: db 0x0A
    col: db ":"


section .bss
    new: resb 16
    val: resb 16
    choice: resb 2


section .text
global _start
_start:
print menu,lenmenu
read choice,2
cmp byte[choice],31H
je next1
cmp byte[choice],32H
je next2
cmp byte[choice],33H
je next3
cmp byte[choice],34H
je next4
cmp byte[choice],35H
je exit
print msgr,lenr
jmp _start


next2:
print msg2,len2
call print_array
print msga,lena
mov rsi,array
mov rdi,array+40
mov byte[count4],5
lb:
movsq
dec byte[count4]
jnz lb
print msg3,len3
call print_total
jmp _start


next1:
print msg2,len2
call print_array
print msg,len
mov rsi,array
mov rdi,array+40
mov byte[count4],5
lb1:
mov rcx,qword[rsi]
mov qword[rdi],rcx
add rsi,8
add rdi,8
dec byte[count4]
jnz lb1
print msg3,len3
call print_total
jmp _start


next3:
call print_array
call other_shift
print msgb,lenb
mov rsi,new1
mov rdi,array+24
mov byte[count4],5
lb11:
mov rcx,qword[rsi]
mov qword[rdi],rcx
add rsi,8
add rdi,8
dec byte[count4]
jnz lb11
print msg3,len3
call print_total_sec
jmp _start

next4:
call print_array
call other_shift
print msgn,lenn
mov rsi,new1
mov rdi,array+24
mov byte[count4],5
lb111:
movsq
dec byte[count4]
jnz lb111
print msg3,len3
call print_total_sec
jmp _start



other_shift:
mov rsi,array
mov rdi,new1
mov byte[count5],5
oi:
mov rcx,qword[rsi]
mov qword[rdi],rcx
add rsi,8
add rdi,8
dec byte[count5]
jnz oi
ret


print_array:
mov rsi,array
mov byte[count],5
up:
mov rbx,rsi
push rsi
call htoa_16
pop rsi
mov rcx,qword[rsi]
push rsi
call htoa_2
pop rsi
add rsi,8
dec byte[count]
jnz up
ret


print_total:
mov rsi,array
mov byte[count],10
up7:
mov rbx,rsi
push rsi
call htoa_16
pop rsi
mov rcx,qword[rsi]
push rsi
call htoa_2
pop rsi
add rsi,8
dec byte[count]
jnz up7
ret


print_total_sec:
mov rsi,array
mov byte[count],8
up71:
mov rbx,rsi
push rsi
call htoa_16
pop rsi
mov rcx,qword[rsi]
push rsi
call htoa_2
pop rsi
add rsi,8
dec byte[count]
jnz up71
ret


htoa_16:
mov rdi,new
mov byte[count2],16
up2:
rol rbx,04
mov dl,bl
And dl,0FH
cmp dl,09
jbe next31
add dl,07
next31:
add dl,30H
mov byte[rdi],dl
inc rdi
dec byte[count2]
jnz up2
print new,16
print col,1
ret


htoa_2:
mov rdi,val
mov byte[count3],16
up3:
rol rcx,04
mov dl,cl
And dl,0FH
cmp dl,09
jbe next41
add dl,07
next41:
add dl,30H
mov byte[rdi],dl
inc rdi
dec byte[count3]
jnz up3
print val,16
print a,1
ret


exit:
mov rax,60
mov rdi,0
Syscall
