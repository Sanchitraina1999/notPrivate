;sorting in increasing and decreasing order using BUBBLE sort ... 
;reading the input from the text file and writing back the result to the same file

%macro mymacro 4
           mov        rax,%1
           mov        rdi,%2
           mov        rsi,%3
           mov        rdx,%4
           syscall
%endmacro

section .data

           menu       : db "********MENU********",0xA
           db         "1. Sort in Increasing order",0xA
           db         "2. Sort in Decreasing order",0xA
           db         "3. Exit",0xA
           lenM       : equ $-menu

           fname      : db 'file.text',0                        ;0 helps to find the file
           warn       : db "Sorry! File can't be opened",0xA
           len        : equ $-warn
           success    : db "File is opened successfully",0xA
           lens       : equ $-success

section .bss
           fd_in      : resb 8
           buffer     : resb 30
           len1       : resb 8
           choice     : resb 2
           cnt1       : resb 2
           cnt2       : resb 2

section .text
           global     _start

_start:
	;_-_-_-_-_-OPENING the FILE_-_-_-_-_

           mymacro    2,fname,2,0777
           mov        qword[fd_in],rax                          ; RAX contains file descriptor value
           BT         rax,63                                    ;63rd bit is 0 if file is successfull opened else it is 1[set] 
           jnc        down                                      ; Jump if condition is em
           mymacro    1,1,warn,len
           jmp        exit
down:
           mymacro    1,1,success,lens
           mymacro    0,[fd_in],buffer,30
           mov        qword[len1],rax
_mainmenu:
           mymacro    1,1,menu,lenM
           mymacro    0,1,choice,2

           cmp        byte[choice],31h
           je         option1

           cmp        byte[choice],32h
           je         option2

           cmp        byte[choice],33h
           jae        exit

	;_-_-_-_-_-Ascending Order_-_-_-_-_

option1:
           call       ascending
           mymacro    1,[fd_in],buffer,qword[len1]
           jmp        _start

	;_-_-_-_-_-_-_Descending order_-_-_-_-_-_-_

option2:
           call       descending
           mymacro    1,[fd_in],buffer,qword[len1]
           jmp        _start	


	;_-_-_-_-_-_-_Procedure to sort in ascending order_-_-_-_-_-_-_

ascending:	
           mov        byte[cnt1],5
up2:
           mov        ax,0
           mov        dx,0
           mov        byte[cnt2],4
           mov        rsi,buffer
           mov        rdi,buffer
up1:
           mov        al,byte[rsi]
           add        rsi,2
           cmp        byte[rsi],al
           jnc        down1
	;Swapping of Number
           mov        dl,byte[rsi]
           mov        byte[rdi],dl
           mov        byte[rsi],al
down1:
           add        rdi,2
           dec        byte[cnt2]
           jnz        up1
           dec        byte[cnt1]
           jnz        up2
           ret

	;_-_-_-_-_-_-_Procedure to sort in descending  order_-_-_-_-_-_-_
descending :	
           mov        byte[cnt1],5
up4:
           mov        ax,0
           mov        dx,0
           mov        byte[cnt2],4
           mov        rsi,buffer
           mov        rdi,buffer
up3:
           mov        al,byte[rsi]
           add        rsi,2
           cmp        byte[rsi],al
           jc         down3
	; Do the Swapping of number...
           mov        dl,byte[rsi]
           mov        byte[rdi],dl
           mov        byte[rsi],al
down3:
           add        rdi,2
           dec        byte[cnt2]
           jnz        up3
           dec        byte[cnt1]
           jnz        up4
           ret
	
	
	

exit:	
	;_-_-_-_-_-_-_CLOSE THE FILE_-_-_-_-_-_-_
           mov        rax,3
           mov        rdi,[fd_in]

	;_-_-_-_-_-_-EXIT_-_-_-_-_-_-_
           mov        rax,60
           mov        rdi,0
           syscall	