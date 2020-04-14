;Write X86/64 ALP to count number of positive and negative
;numbers from the array

%macro print 2
           mov           rax,1
           mov           rdi,1
           mov           rsi,%1
           mov           rdx,%2
           syscall
%endmacro

%macro exit 0
           mov           rax,60
           mov           rdi,0
           syscall
%endmacro

section .data
           posmsg        db "Count of Positive Integeres : "
           lenposmsg     equ $-posmsg
    
           negmsg        db "Count of Negative Integeres : "
           lennegmsg     equ $-negmsg

           newLine       db "",0xA
           lennewLine    equ $-newLine

           array         db 0xAA,0x0A,0x8A,0x0A,0x0A            ;if 1st bit is from 0 to 7, then positive else negative
           size          db 05h
           positive      db 0h
           negative      db 0h

section .text
           global        _start

_start:
           mov           rsi,array
above:

           mov           ax,word[rsi]                           ;word - 16 bit (2 bytes)  and byte - 8 bit
           bt            ax,7                                   ;tests the 7th bit, if set then negative moves from ax register to carry flag
           jc            incrementNegative                      ;jc - jump if carry flag is Set
           inc           byte[positive]
           jmp           afterIncrementNegative

incrementNegative:
           inc           byte[negative]

afterIncrementNegative:
           inc           rsi
           dec           byte[size]
           jnz           above

           add           byte[positive],30h
           add           byte[negative],30h

           print         posmsg,lenposmsg
           print         positive,1

           print         newLine,lennewLine

           print         negmsg,lennegmsg
           print         negative,1

           print         newLine,lennewLine

           exit