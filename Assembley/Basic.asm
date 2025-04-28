# Basic.asm

.global _start
.intel_syntax

#----------------------------#
# DATA SECTION
#----------------------------#
.section .data

#----------------------------#
# TEXT SECTION
#----------------------------#
.section .text
    
_start:

    # Syscall() - PRINT
    push 0x0A434241        #  ASCII :  A B C \n
    mov %EAX, 4                # syscall no.
    mov %EBX, 1                 # stdout
    mov %ECX, %ESP         # Pointer to the string we want to print in ECX
    mov %EDX, 4                 # Size of the string or no. of bytes to print
    int 0x80    

    # Syscall() - EXIT
    mov %EAX, 1                  # syscall no.
    mov %EBX, 65               # 
    int 0x80
    
    # syscall

