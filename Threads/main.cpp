/*

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

    cout << "accum = " << accum << endl;
    
    return 0;
}