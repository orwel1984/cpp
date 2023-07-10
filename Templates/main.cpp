//
//  main.cpp
//  Sorting
//
//  Created by tanweer ali on 28/05/2021.
//

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <cmath>


// Example 1: TEMPLATE CLASS EXAMPLE
// A simple generic Array with fixed size 2.
template <typename T>
class ArrayOf2
{
public:
         T& operator[](size_t i)       { return a_[i]; }
   const T& operator[](size_t i) const { return a_[i]; }
                         T sum() const { return a_[0] + a_[1]; }
private:
    T a_[2];
};

// Usage:
// ArrayOf2<double> d;
// ArrayOf2<int> i;
// i[0] = 1;
// i[1] = 5;

// Example 2: Template with non-type parameter
// An Array class with a dynamic fixed-size array.
template <typename T, size_t N>
class Array {
public:
   T& operator[](size_t i) {
      if (i >= N) throw std::out_of_range("Bad index");
      return data_[i];
   }
private:
   T data_[N];
};

// Usage:
// Array<int, 2> i;
// i[0] = 1;
// i[1] = 5;
// Array<double, 4> i;


// Example 3:
// TEMPLATE VARIABLE
template <typename T>
constexpr T pi = T(3.14159265358979323846264338327950288419716939937510582097494459230781L);

// Usage:
// pi<float> ;      // 3.141592
// pi<double>;      // 3.141592653589793
// pi<int> ;        // 3

// Example 4:   Template Template parameter.
// The following function resequence() takes a container of one type e.g. std::vector
// and converts it into a container of another type eg. std::deque.
// e.g. a call like:
//    const std::vector<int> v { 1, 2, 3, 4, 5 };
//    auto d = resequence<std::deque>(v); // deque with 1, 2, 3, 4, 5

// Form 1: non-variadic
template <  template <typename> class Out_container,
            template <typename> class In_container,
            typename T>
Out_container<T> resequence(const In_container<T>& in_container)
{
    Out_container<T> out_container;
    for (auto x : in_container) {
        out_container.push_back(x);
    }
    return out_container;
}

// Form 2: non-variadic
// The following form works with std::vector, since std::vector isn't a container that receive one 
// type template parameter; it's a container that receive two type template parameter 
// (the second one with a default type: std::allocator<T> where T is the first one). 
// So change above to more flexible container with an variadic list of template types of arguments.
template <  template <typename...> class Out_container,
            template <typename...> class In_container,
            typename... T>
Out_container<T...> resequence(const In_container<T...>& in_container)
{
    Out_container<T...> out_container;
    for (auto x : in_container) {
        out_container.push_back(x);
    }
    return out_container;
}

// Example 5:   Template Meta Programming.

template <int N>
struct Factorial
{
    static const int value = N * Factorial<N-1>::value; // recursive!
};

template <>                 // specialization
struct Factorial<0>
{
  static const int value = 1;
};


/// Example 6:   USING SFINAE.
//
//  Consider the distance function below which takes four paramters.
//
//    template <typename T>
//    T   distance(T x1, T y1, T x2, T y2)
//    {
//        T tmp1 = a1 - b1;
//        T tmp2 = a2 - b2;
//        return std::sqrt( tmp1*tmp1 + tmp2*tmp2 );
//    }
//
//  We can restrict it to only float/double types using SFINAE.
template <typename T>   struct restrictor { };
template<>              struct restrictor<float>    { typedef float result; };
template<>              struct restrictor<double>   { typedef double result; };

template <typename T>
typename restrictor<T>::result 
distance(T x1, T y1, T x2, T y2)
{
    T tmp1 = x1 - x2;
    T tmp2 = y1 - y2;
    return std::sqrt( tmp1*tmp1 + tmp2*tmp2 );
}

//-----------------------------------------------------
// Exmaple 7: CRTP
//-----------------------------------------------------

//-----------------------------------------------------
// Exmaple 8: Fold expressions with Templates in C++14
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
// Example 9: 
// A template which groups whatever datatypes are passed 
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

int main(int argc, const char * argv[]) 
{
    
    std::cout <<"\n-----------------------";
    std::cout <<"\nExample 1:-";   
    std::cout <<"\n-----------------------";

    ArrayOf2<int> i;
    i[0] = 1;
    i[1] = 5;
    std::cout << std::endl << i.sum() <<"\n";     //6
    
    ArrayOf2<double> x;
    x[0] = -3.5;
    x[1] = 4;
    std::cout << x.sum() <<"\n";    //0.5
    
    std::cout <<"\n-----------------------";
    std::cout <<"\nExample 2:-";
    std::cout <<"\n-----------------------";
    Array<int, 5> a; // OK
    std::cout << std::endl << a[0] <<"\n";      // 3

    std::cout <<"\n-----------------------";
    std::cout <<"\nExample 3:-";
    std::cout <<"\n-----------------------";
    std::cout << std::endl << pi<float> ;   // 3.141592
    std::cout << std::endl << pi<double>;    // 3.141592653589793
    std::cout << std::endl << pi<int> ;      // 3
    
    // Example 4: Template-Template parameters
    std::cout <<"\n-----------------------";
    std::cout <<"\nExample 4:-";
    std::cout <<"\n-----------------------";
    std::vector<int> v { 1, 2, 3, 4, 5 };
    auto d = resequence<std::deque>(v); // deque with 1, 2, 3, 4, 5
    for(auto i:d){
        std::cout << std::endl << i;      // 3
    }
    
    //Example 5: Template Meta Programming
    std::cout <<"\n-----------------------";
    std::cout <<"\nExample 5:-";
    std::cout <<"\n-----------------------";
    std::cout <<"\nFactorial of 4: " << Factorial<4>::value <<"\n";      // 3
    
    //Example 6: SFINAE
    std::cout <<"\n-----------------------";
    std::cout <<"\nExample 6:-";
    std::cout <<"\n-----------------------";
    std::cout << "\nThe distance between (0,0) & (2,2): "
              << distance(0.0,0.0,2.0,2.0) <<"\n";      // 2.82843

    // distance(0,0,2,2);  // ERROR:   main.cpp:257:5: error: no matching function for call to 'distance'

    
   std::cout <<"\n-----------------------";
   std::cout <<"\nExample 7:-";
   std::cout <<"\n-----------------------";
   std::cout   << std::endl
               <<sum(1,2,3,4,5,6,7)
               << std::endl;

   std::cout <<"\n-----------------------";
   std::cout <<"\nExample 8:-";
   std::cout <<"\n-----------------------";
   auto g = makeGroup(3, 2.2, std::string("xyz"), 5);
   std::cout<< std::endl << static_cast<std::string>(g) << std::endl ;
   std::cout<< std::endl <<         static_cast<int>(g) << std::endl ;
   std::cout<< std::endl <<      static_cast<double>(g) << std::endl ;
    
   return 0;
}
