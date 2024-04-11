# Assembley

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

        mov     eax, 1

        # epilogue
        pop     rbp
        ret
```

The first two lines and last two lines are just the function pre-requisite and post. The rerturn value is being passed into **EAX** register. 

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

Then let'c compile and print debug symbols and text-sections:

```bash
gcc -c a.cpp
nm --debug-syms --demangle   a.out
objdump --no-show-raw-insn -dC a.o
```

```cpp
// # Symbol-Table

0000000000000000 T func()
0000000000000008 T _main
0000000000000000 t ltmp0
0000000000000028 s ltmp1


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

As you can see there are two symbols func( ) and main( ) in the text sections now. The assembley is generated for the ARM platform this time.

