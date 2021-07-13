
// #include <iostream>
// #include <vector>
#include <bits/stdc++.h> // Works with GCC, includes all standard headers

class Base
{
};

/*
*************************
  1. Default Methods:
*************************

    -   For the empty class Base above the compiler will automatically generate 
        the following 6 defualt methods: 

            // since C++98
            Base() {}                           // default constructor
            ~Base() {}                          // default destructor
            Base(const Base& ) {}               // copy contructor
            Base& operator= (const Base& ) {}   // copy assignment
            
            // since C++1            
            Base(Base&& ) {}                    // move contructor
            Base& operator= (Base&& ) {}        // move assignment


        Notice that move functions take a non-const argument.

*/

#define deb(x) std::cout << #x << ": " << x << "\n";

//  FOLD Expressions - C++17
template <typename... T>
void print(T &...args)
{
    ((std::cout << args), ...);
}

int main()
{
    int x(100);

    deb("hi");

    print("\nhello", "\nbye bye");

    return 0;
}