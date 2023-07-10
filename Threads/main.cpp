/*

    -----------------------
    Processes
    -----------------------

    The most central concept in any operating system is the 
    Process: "an abstraction of a running program".

    A process is just an instance of an executing program, 
    including the current values of the program counter, 
    registers, and variables.

    - Process Creation:
    Process creation happens on system startup and later when
    every time the process creation SystemCall is executed.
    Processes that stay in the background to handle some activity 
    such as emails, printing, and so on are called daemons.

    - In distributed programming an application consists of 
    multiple processes cooperate together over different hosts
    machine.


    -----------------------
    Threads
    -----------------------
    -   A thread is a sequence of instructions, 
        given to the CPU by an application process.

    -   Hardware & Software Threads:   

    -   Hardware-Threads:
        ------------------
        A single core of the CPU can run one 
        only one instruction of one thread at any one time.
        The threads that directly run instructions on the CPU core
        are called Hardware Threads.

        -   The total no. of Hardware Threads determine how many 
            threads can actually run in parallel on a system.

        -   Hyper-Threading: This is a hardware feature by which 
            each core can run multiple hardware threads, thus appearing 
            to the OS as if more physical cores are present on the system.
            (First introduced in Intel Pentium 4)

    -   Software-Threads:
        ------------------
        These are the threads which the OS manages across the entire 
        system for all processes/applications.
        -   The OS schedules Software-Threads for execution on Hardware-Threads.
        -   It is possible to create more Software Threads than 
            the no. of available Hardware Threads on a system. 
            But the Total no. of Software-Threads is also a 
            limited resource.

        -   OverSubscription:
            When more Software-Threads are ready to run than the total no. of available 
            Hardware Threads. This is a problem because it leads to threads sitting idle.

        -   Thread-Scheduler:
            This is an important component of the OS which deals with 
            scheduling Software-Threads on the hardware.            
            -   Thread-Pools: 
                modern schedulers use system-wide thread pools, which deals with
                problems like oversubscription, load-balancing etc. through
                work-stealing algorithms.

    -----------------------
    std::thread
    -----------------------
    -   Objects of this class  

    -----------------------
    Callbacks
    -----------------------
    A callback function is a function passed into another function as an argument.
    The callback is then invoked later to signal completion of some kind of routine or action.

    Compile Instrunctions:
    -   g++ main.cpp -o main -std=c++0x -pthread


    Run Instrunctions:
    
        Try 
        -  ./main

        And also using bash script:
        -   for i in {1..1000}; do ./main; done | sort | uniq -c

*/

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

std::mutex accum_mutex;

void square(int& accum, int x) {
    //     accum += x * x;

    int temp = accum;
    temp += x*x;
    accum = temp;
}

/**
 * @brief   An example program to introduce the concepts of threads.
 *          It creates a pool of threads in a std container and waits for them to join
 *          the main thread.
 * 
 * @return Returns 0 when execution completes successfully.
 * 
 */

int main() {
    
    int accum = 0;          // final result

    std::vector<std::thread> threads;

    for (int i = 1; i <= 20; i++) {

        // Note: use std::ref() to pass a reference to a variable to thread instead of & 
        threads.push_back( std::thread(&square, std::ref(accum), i) );
    }
  
    // wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "accum = " << accum << std::endl;

    // max range of int (signed) = 2147483647
    int32_t a = 1000000000;
    int32_t b = 1500000000; 
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a+b/2 = " << (a+b)/2 << std::endl;
    
    return 0;
}