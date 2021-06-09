//
//  main.cpp
//  Sorting
//
//  Created by tanweer ali on 28/05/2021.
//

#include <iostream>
#include <vector>
#include <string>


//-----------------------------------------------------
// Exmaple 1: Fold expressions with Templates in C++14
//-----------------------------------------------------

//// C++17 fold expression
//template <typename ... T>
//auto sum(const T& ... x) {
//  return (x + ...);
//}

// C++14 - no fold expressions
// This is the standard technique for unraveling the parameter packs in variadic templates
template <typename T1>
auto sum(const T1& x1) {
   return x1;
}

template <typename T1, typename ... T>
auto sum(const T1& x1, const T& ... x) {
   return x1 + sum(x ...);
}

//-----------------------------------------------------

//-----------------------------------------------------
// Example 2: 
// A template which groups whatever datattypes are passed 
// to it and then casts the value which is present
//-----------------------------------------------------

template <typename ... T>
   struct Group;

template <typename T1>
   struct Group<T1> {
       T1 t1_;
       Group() = default;
       explicit Group(const T1& t1) : t1_(t1) {}
       explicit Group(T1&& t1) : t1_(std::move(t1)) {}
       explicit operator const T1&() const { return t1_; }
       explicit operator T1&() { return t1_; }
};

template <typename T1, typename ... T>
   struct Group<T1, T ...> : Group<T ...> {
       T1 t1_;
       Group() = default;
       explicit Group(const T1& t1, T&& ... t)
                    : Group<T ...>(std::forward<T>(t) ...), t1_(t1) {}
       explicit Group(T1&& t1, T&& ... t)
                    : Group<T ...>(std::forward<T>(t) ...), t1_(std::move(t1)) {}
       explicit operator const T1&() const { return t1_; }
       explicit operator T1&() { return t1_; }
};

template <typename ... T>
auto makeGroup(T&& ... t) {
   return Group<T ...>(std::forward<T>(t) ...);
}
//----------------------------------------------------
int main(int argc, const char * argv[]) {
    
    std::cout   << std::endl
                <<sum(1,2,3,4,5,6,7)
                << std::endl;
    
    auto g = makeGroup(3, 2.2, std::string("xyz"), 5);
    std::cout<< std::endl << static_cast<std::string>(g) << std::endl ;
    std::cout<< std::endl <<         static_cast<int>(g) << std::endl ;
    std::cout<< std::endl <<      static_cast<double>(g) << std::endl ;
    
    return 0;
}
