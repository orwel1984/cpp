# Assembly

A program is just a list of assembley instructions. 

This simple .cpp program which just returns 1, generates the following assembley (using GodBolt):

```cpp
int main()
{
    return 1;
}
```

```bash
# Assembley Code
main:
        # prologue
        push    rbp
        mov     rbp, rsp

        # return value
        mov     eax, 1

        # epilogue
        pop     rbp
        ret
```

- Prolog:  When the function starts, the first thing to do is point the RBP (Base-Pointer) to the top of the stack. 

- Epilog: 
Pop the old value of the RBP.  Call the return instruction RET. 

- Return Value:
The rerturn value is passed through **EAX**. 

In the Intel Assembley format the first operand is DESTINATION.


```bash
otool -x -v a.out
```

```bash
nm --debug-syms --demangle a.out

#Linux
readelf -a a.out
```

## Display Text Section of a Binary

Consider another simple example with two functions:

```cpp
// a.cpp 

int func(){return 1;}
int main(){return func();}
```

Then let'c compile and print debug symbols:

```bash
gcc -c a.cpp
nm --debug-syms --demangle   a.out
```

```cpp
// # Symbol-Table
0000000000000000 T func()
0000000000000008 T _main
0000000000000000 t ltmp0
0000000000000028 s ltmp1
```
Note the capital T before func() and main().

And let's print the text-section.
```cpp
objdump --no-show-raw-insn -dC a.o
```

```cpp
// Text Section

(__TEXT,__text) section
__Z4funcv:
0000000000000000	mov	w0, #0x1
0000000000000004	ret

_main:
0000000000000008	sub	sp, sp, #0x20
000000000000000c	stp	x29, x30, [sp, #0x10]
0000000000000010	add	x29, sp, #0x10
0000000000000014	stur	wzr, [x29, #-0x4]
0000000000000018	bl	0x18
000000000000001c	ldp	x29, x30, [sp, #0x10]
0000000000000020	add	sp, sp, #0x20
0000000000000024	ret
```

The assembley is generated for the ARM platform where the program was compiled for.

