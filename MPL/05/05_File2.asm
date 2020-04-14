
section .bss
extern buffer,len1,result,find

cnt  : resb 8



section .text
global main2
main2:


;*******Procedure for calculating the Spaces in message********
global  spc:

spc:
	mov rsi,buffer
	mov rcx,qword[len1]
	mov qword[cnt],rcx
	mov rcx,0
	;mov ax,0
up:
	cmp byte[rsi],0x20
	jne down
	inc cx
down:
	inc rsi
	dec qword[cnt]
	jnz up
	cmp cl,09
	jbe down3
	add cl,07h
down3:
	add cl,30h
	mov byte[result],cl
	ret

;******Procedure for Calculating the lines in message**********
global ent:

ent:
	mov rsi,buffer
	mov rcx,qword[len1]
	mov qword[cnt],rcx
	mov rcx,0
	;mov ax,0
up2:
	cmp byte[rsi],0x0A
	jne down2
	inc cx
down2:
	inc rsi
	dec qword[cnt]
	jnz up2
	cmp cl,09h
	jbe down5
	add cl,07h
down5:
	add cl,30h
	mov byte[result],cl
	ret

;******Procedure for calculating occurance of a character in message*****

global Occ:

Occ:
	mov rsi,buffer
	mov rcx,qword[len1]
	mov qword[cnt],rcx
	mov rcx,0
	mov ax,0
	mov al,byte[find]
up4:
	cmp byte[rsi],al
	jne down4
	inc cx
down4:
	inc rsi
	dec qword[cnt]
	jnz up4
	ret

	
	


	
	


