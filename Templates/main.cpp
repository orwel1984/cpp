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
#include <memory>


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

// Example 3:
// TEMPLATE VARIABLE
template <typename T>
constexpr T pi = T(3.14159265358979323846264338327950288419716939937510582097494459230781L);


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
// The following form works with std::vector, since std::vector isn't a container that 
// receive one type template parameter; it's a container that receive two type template 
// parameter (the second one with a default type: std::allocator<T> where T is the first one). 
// So change above to more flexible container with an variadic list of template types of arguments
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
typename restrictor<T>::result distance(T x1, T y1, T x2, T y2)
{
    T tmp1 = x1 - x2;
    T tmp2 = y1 - y2;
    return std::sqrt( tmp1*tmp1 + tmp2*tmp2 );
}


//-----------------------------------------------------
// Exmaple 7: Fold expressions with Templates in C++14
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
// Example 8: 
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

//-----------------------------------------------------
// Example 9: CRTP - Static Polymorphism
//  
// Curiously Recurring Template Pattern
// In This example we will use Static Polymorphism which
// is based on CRTP pattern for templates.
//-----------------------------------------------------
template <class Derived>
struct Base
{
    //public interface
    void interface()
    {
        // calls a Derived::implementation() method, 
        // which is not even a member of the Base class.
        // ( but has to be a public method in Derived )
        static_cast<Derived*>(this)->implementation();
    }
};

class Derived : public Base<Derived>
{
public:
    void implementation()
    {
        std::cout<<"\nCalling Derived::implementation();\n\n";
    }
};

// USAGE:
// Derived derived;
// derived.interface();

//-----------------------------------------------------
// Example 10: CRTP - Inject Behaviour 1 - Cloneable
//  
// Curiously Recurring Template Pattern
// In This example we will show how CRTP can inject 
// behaviour into the derived classes.
// e.g. we can inject a clone() method into any object, 
// which is able to return a copy of the concrete-type 
// with a single implementation in one base class.
//-----------------------------------------------------

template <class Derived>
struct Cloneable
{
    Derived* clone()
    {
        // following line is calling the copy constructor:
        // Derived::Derived(Derived const &)
        // by casting the (*this) into a const-ref
        return new Derived( static_cast<Derived const&>(*this) );        
    }
};

struct Shape : Cloneable<Shape>
{
    int area = {0};
};
// USAGE:
// Shape shape;
// shape.area = 100;
// auto clone = shape.clone();

//-----------------------------------------------------
// Example 11: CRTP - Inject Behaviour 2 - enable_shared_from_this 
//  
// This example shows a sample implementation of 
// enabled_shared_from_this.
// See https://www.youtube.com/watch?v=9TFV2JxX7L0
// Any class T which inheirts from ali::enable_shared_from_this<T>
// will get injected a shared_from_this(); function with a weak_ptr.
// Note: The derived class T using enabled_shared_from_this must ensure,
// that it's object is only managed by std::shared_ptr<T>.
// It can do so by making it's constructor private and provide a static 
// factory method to ensure that some shared_ptr with a control-block 
// is already pointing to this object (see Meyers )
//-----------------------------------------------------

namespace ali{

template <class T>
struct enable_shared_from_this
{
private:
    // define a private weak_ptr field
    mutable std::weak_ptr<T> weak_this_;

public:
    std::shared_ptr<T> 
    shared_from_this()
    {
        // create a new shared ptr from the weak_ptr
        std::shared_ptr<T> p(weak_this_);
        return p;
    }

    // following function is just the const version of the above
    std::shared_ptr<T const> 
    shared_from_this() const
    {
        std::shared_ptr<T const> p(weak_this_);
        return p;
    }

};
} // namespace ali

//-----------------------------------------------------
// Example 10: 
// Type Traits
//-----------------------------------------------------


//-----------------------------------------------------
// Example 11: 
// SFINAE
// Substituion Failure Is Not an Error
//-----------------------------------------------------

//-----------------------------------------------------
//-----------------------------------------------------
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

    //  distance(0,0,2,2);  // ERROR:   int not allowed.

    
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


   std::cout <<"\n-----------------------";
   std::cout <<"\nExample 9:-";
   std::cout <<"\n-----------------------";
   Derived derived;
   derived.interface();

   std::cout <<"\n-----------------------";
   std::cout <<"\nExample 10:-";
   std::cout <<"\n-----------------------";
   Shape shape;
   shape.area = 100;
   auto clone = shape.clone();
   std::cout<< "\n" <<"clone's area:" << clone->area << "\n";


   return 0;
}
