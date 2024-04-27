# GDB

- Run GDB using: 

```bash
gdb path/to/binary
``` 

Make sure to compile your program with -g option. 
Also set the optimization level to -Os to get proper assembley stadktraces all the way into libc.

## Common Commands

- list

- p   [variable-name]

- break  [function-name]

- r   
continue executing the program.

- disassemble

show disassembly around current instruction to be executed.

- **bt** 

Backtrace 

```
(gdb) bt

#0  func1 () at a.cpp:5

#1  0x0000fffff7e27780 in __libc_start_call_main (main=main@entry=0x4005b4 <_start+52>, argc=argc@entry=1, argv=argv@entry=0xfffffffffb18)
    at ../sysdeps/nptl/libc_start_call_main.h:58

#2  0x0000fffff7e27858 in __libc_start_main_impl (main=0x4005b4 <_start+52>, argc=1, argv=0xfffffffffb18, init=<optimized out>, 
    fini=<optimized out>, rtld_fini=<optimized out>, stack_end=<optimized out>) at ../csu/libc-start.c:360

#3  0x00000000004005b0 in _start ()
```

- n

Step over to next C++ instruction.

- c

continue until next breakpoint


- stepi 

Step over a single assembley instruction


- tui enable


- set data read/write breakpoints

```
watch <variable-name>
```

OR 

```bash
info address <varible-name>

rwatch *<result-address-of-above>
```