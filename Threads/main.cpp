/*

    Processes & Threads: 
    -----------------------

    The most central concept in any operating system is the 
    Process: "an abstraction of a running program".

    A process is just an instance of an executing program, 
    including the current values of the program counter, 
    registers, and variables.

    - Process Creation:
    Process creation happens on system startup and later when
    evrytime the process creation SystemCall is executed.

    Processes that stay in the background to handle some activity 
    such as emails, printing, and so on are called daemons.

    - Process Termination:
    Process creation happens on system startup and later when
    the process creation System-Call is executed.


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