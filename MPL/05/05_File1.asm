%macro mymacro 4
           mov        rax,%1
           mov        rdi,%2
           mov        rsi,%3
           mov        rdx,%4
           syscall
%endmacro

section .data

menu : db "-----File Character Locater-----",0x0A
           db         " 1.Number of Spaces",0x0A
           db         " 2.Number of lines ",0x0A
           db         " 3.Occurance of a particular character",0x0A
           db         " 4.Exit",0x0A
lenm : equ $-menu

fname : db 'a.txt',0			;0 helps to find the file 
success : db "File opened successfully",0x0A,0x0A
lens: equ $-success
warn: db "Error opening the file",0x0A
len : equ $-warn
ans1 : db "Number of the spaces in text ",0x0A
lena1: equ $-ans1
ans2 : db "Number of the lines in text ",0x0A
lena2: equ $-ans2
ans3 : db "Number of occurence of the given character is "
lena3:equ $-ans3
query : db "Enter the character you want to find",0x0A
lenq : equ $-query

enterkey: db 0x0A

section .bss
global fd_in,buffer,choice,len1,result,find
fd_in : resb 8
buffer : resb 100
choice : resb 2
len1: resb 8
find: resb 2

result : resb 1



section .text
global _start
_start:

;***************OPEN THE FILE******************
           mymacro    2,fname,2,0777
	;rax return the file descriptor
           mov        qword[fd_in],rax
           BT         rax,63
           jnc        down
           mymacro    1,1,warn,len
           jmp        exit
down:
           mymacro    1,1,success,lens
           mymacro    0,[fd_in],buffer,100
	
	;rax return the no of byte recievd..stored in len1 var
           mov        qword[len1],rax
menup:
           mymacro    1,1,menu,lenm
           mymacro    0,1,choice,2
           cmp        byte[choice],31h
           je         space
           cmp        byte[choice],32h
           je         enter
           cmp        byte[choice],33h
           je         letter
           cmp        byte[choice],34h
           jae        exit



;*********CALL THE PROCEDURE TO CALCULATE THE NUMBER OF SPACES*******
space:
           extern     spc
           call       spc
           mymacro    1,1,ans1,lena1
           mymacro    1,1,result,1
           mymacro    1,1,enterkey,1
           jmp        menup
	
;*********CALL THE PROCEDURE TO CALCULATE THE NUMBER OF LINE*******
enter:
           extern     ent
           call       ent
           mymacro    1,1,ans2,lena2
           mymacro    1,1,result,1
           mymacro    1,1,enterkey,1
           jmp        menup

;*********CALL THE PROCEDURE TO CALCULATE THE OCCURANCE OF LETTER*****

letter:
           mymacro    1,1,query,lenq
           mymacro    0,1,find,2
           extern     Occ
           call       Occ
           cmp        cx,09
           jbe        down5
           add        cx,07H
down5:
           add        cx,30H
           mov        byte[result],cl
           mymacro    1,1,ans3,lena3
           mymacro    1,1,result,1
           mymacro    1,1,enterkey,1
           jmp        menup

	

;*************CLOSE THE FILE **********************
exit:	
           mov        rax,3
           mov        rdi,[fd_in]


           mov        rax,60
           mov        rdi,0
           syscall