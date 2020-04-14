%macro scall 4
           mov        rax,%1
           mov        rdi,%2
           mov        rsi,%3
           mov        rdx,%4
           syscall
%endmacro

section .data
warn : db "File is not opened successfully",0x0A
lenw : equ $-warn


section .bss
fname : resb 10
fname1 : resb 10
fd_in1:resb 8
fd_in2:resb 8
len1: resb 8
buffer : resb 100

section .text
global _start

_start:

;*********PROCESS THE COMMAND LINE ARGUMENT*********

           pop        rbx
           pop        rbx
           pop        rbx
           cmp        byte[rbx],'T'
           je         type
           cmp        byte[rbx],'C'
           je         copy
           cmp        byte[rbx],'D'
           je         delete



;*************TYPE THE CONTENT OF THE FILE*************
type :
           pop        rbx
           call       filename
	; we got the filename...
	; open the file
           mov        rax,2
           mov        rdi,fname
           mov        rsi,2
           mov        rdx,0777
           syscall

           mov        qword[fd_in1],rax
           BT         rax,63
           jnc        down1
           scall      1,1,warn,lenw
           jmp        exit
down1:
           mov        rax,0
           mov        rdi,[fd_in1]
           mov        rsi,buffer
           mov        rdx,100
           syscall
	
	;rax will return the number of byte read
           mov        qword[len1],rax
           scall      1,1,buffer,len1
	
	;CLOSE THE FILE		
           mov        rax,3
           mov        rdi,[fd_in1]
           syscall
           jmp        exit




;*************COPY THE CONTENT OF THE FILE************
copy:
           pop        rbx
           call       filename
	;we get file name
	;open the file 
           mov        rax,2
           mov        rdi,fname
           mov        rsi,2
           mov        rdx,0777
           syscall
	;return the file descriptor
           mov        qword[fd_in1],rax
           BT         rax,63
           jnc        down2
           scall      1,1,warn,lenw
           jmp        exit
down2:
           mov        rax,0
           mov        rdi,[fd_in1]
           mov        rsi,buffer
           mov        rdx,100
           syscall

           mov        qword[len1],rax
	
           mov        rax,3
           mov        rdi,[fd_in1]
           syscall
	
           mov        rbx,0
           pop        rbx
           call       filename1
	;we got the file name
	;open that file
           mov        rax,2
           mov        rdi,fname1
           mov        rsi,2
           mov        rdx,0777
           syscall
	
           mov        qword[fd_in2],rax
           BT         rax,63
           jnc        down3
           scall      1,1,warn,lenw
           jmp        exit
down3:
           mov        rax,1
           mov        rdi,[fd_in2]
           mov        rsi,buffer
           mov        rdx,qword[len1]
           syscall
           jmp        exit




;***********DELETE THE FILE**********************
delete:
           pop        rbx
           call       filename
           mov        rax,87
           mov        rdi,fname
           syscall
           jmp        exit
	

;***********FILENAME****************
filename:
           mov        rsi,rbx
           mov        rdi,fname
           cld
up:
           cmp        byte[rsi], 0
           je         down
           movsb
           jmp        up
down:
           ret
;*********FILENAME@*************
filename1:
           mov        rsi,rbx
           mov        rdi,fname1
           cld
up4:
           cmp        byte[rsi], 0
           je         down4
           movsb
           jmp        up
down4:
           ret
;************EXIT********************

exit:
           mov        rax,60
           mov        rdi,0
           syscall