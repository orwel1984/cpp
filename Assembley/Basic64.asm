#Basic.asm  64-bit

.global _start
.intel_syntax

#----------------------------#
# DATA SECTION
#----------------------------#
.section .data
    msg: .ascii "Hello World\n"

#----------------------------#
# TEXT SECTION
#----------------------------#
.section .text
    
_start:

    # Syscall() - Print  through stack
    push 0x0A434241        #  ASCII  for characters in reverse:  A B C \n
    mov %RAX, 1                # syscall no.
    mov %RDI, 1                 # file-descriptor for STDOUT in linux
    mov %RSI, %RSP         # Address of the string we want to print
    mov %RDX, 4                # Length of the string
    syscall

    # Syscall() - Print through global variable
    mov %RAX, 1                # syscall no.
    mov %RDI, 1                 # file-descriptor for STDOUT in linux
    lea %RSI, [msg]            # Address of the string we want to print
    mov %RDX, 12              # Length of the string
    syscall

    # Syscall() - EXIT
    mov %RAX, 0x3C          # syscall no.
    mov %RDI, 65               # ERROR-CODE
    syscall
