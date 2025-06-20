

## C++ Locks, Atomics & Memory-Order


### Critical-Section
Mutexes & Atomics are the two different ways to specify the same thing i.e. the **critical section** of the code.

Critical-Sections are reigons of your source code, which you want only one thread to enter at one time. 

Hence, the term MUTEX satnds for **mutual-exclusion**. 
While **Atomic** is more from the operation point of view, i.e. other threads only see the state of the system either before or after the operation, but not anything in between when all the steps of the operation has'nt finished yet.


https://www.youtube.com/watch?v=A8eCGOqgvH4
