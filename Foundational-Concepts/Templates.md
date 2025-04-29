# Templates

Helps reduce code duplication by minimizing the no. of function overloads you have to write, and forces you to think in more generic way about your paramters. 


- [ Functors ](#functors)
- [RAII](#raii)
- [Concepts](#concepts)
- [Policy Classes](#policy-classes)
- [CRTP](#crtp)
- [Type Traits](#type-traits)
- [Tag Dispatching](#tagdispatch)
- [SFINAE](#sfinae)
    - [Point Class](#1-generic-point)
- [Factorial](#factorial)


References:
1. https://www.youtube.com/watch?v=urshrBatNo4 
2. 


## Functors
An object or class which is callable like a function. 
- It is like a function-ptr but which has a state.
- Used as callbacks
- Used to define lambdas

Overload the operator ( )

```cpp
struct mod
{
     // constructor: init functor's state here
    mod(int m) : m_(m){ }     

    // overload the function call operator ( ) 
    int operator()  (int number) { return number%m_}

    // state
    int m_; 
}

// Usage
// set the number we want to take modulus with with
mod modder(5);

cout << modder(42);         // output = 2 =  42 % 5

```

## RAII
See [document](./RAII.md)

## Concepts

Provides a set of requirements, as valid expressions, that must be met by a template type.

Here is a concept for **ForwardIterator**  and **BiDirectionalIterator** types:

|      **Requirements**      	| **Forward Iterator** 	| **BiDirectional Iterator** 	|
|:--------------------------:	|:--------------------:	|----------------------------	|
| Can be default constructed 	|         X a;         	|            X a;            	|
|                            	                    |         X();         	|            X();            	|
|   Can be Copy Constructed  	|        X b(a);       	|           X b(a);          	|
|                            	                    |        b = a;        	|           b = a;           	|
|    Equality Comparisons    	    |        a == b        	|           a == b           	|
|                            	                    |        a != b        	|           a != b           	|
|        Dereferencing       	         |          *a          	|             *a             	|
|                            	                    |         a->m         	|            a->m            	|
|     Can be incremented     	    |  ++a<br>a++<br>*a++  	|     ++a<br>a++<br>*a++     	|
|     Can be decremented     	    |                      	|     --a<br>a--<br>*a--     	|


As you can see that BiDirectional iterator type support a similar requirements to ForwardIterator except that it can be additionally decermented.

## Policy Classes

A policy class is a template paramter that specializes behaviour and is selected at compile time.

**Examples**

Standard library has a lot of classes that use policies e.g. std::string 
```cpp
// std::string is defined as a basic_string
std::basic_string <charT, traits, Alloc>

namespace std{
    typedef basic_string<char> string;
}

// here Alloc is a policy and can change memory allocation behaviour of the string at compile time.
```

Another example of a policy class can be a pointer-wrapper class that checks for a pointer being nullptr or not:

```cpp
// Here is a simple pointer_wrapper class that takes any pointer of any kind and wraps it with different behaviours based on the policy chosen.
template <  typename T, 
                    typename CheckingPolicy=NoChecking, 
                    typename BadPointerPolicy=DoNothing>
class pointer-wrapper
{
public:
    pointer-wrapper() : _value(0){ }
    explicit pointer-wrapper(T* ptr) : _value(ptr){ }

    T* operator*()
    {
        // so whenever this class is dereferenced with * 
        // it will first check if the pointer is nullptr or not.
        // And adjust it's behaviour according to the policy set.
        if( !CheckingPolicy::check_pointer(_value) )
        {
            return BadPointerPolicy::handle_bad_pointer(_value);
        }
        else
        {
            return _value;
        }
    }

private: 
    T* _value;
}

// Define Policies: 

struct NoChecking
{
    template <typename T>
    static bool check_pointer(T* ptr) { return true;}
}

struct NullChecking
{
    template <typename T>
    static bool check_pointer(T* ptr) { return (p!=nullptr);}
}

struct DoNothing
{
    template <typename T>
    static T* handle_bad_pointer(T* ptr) 
    { 
        std::cout << "Pointer is moldy";
        return ptr;
    }
}

void main()
{
    pointer_wrapper<int>    ptr<new int>;
    *ptr = 42;
    std::cout<<"Your number: " << *ptr;

    // ERROR:   following lines will give segmentation-fault
    //                 since we do'nt init the pointer correctly with new.
    //                 Since defualt policy is NoChecking, no warning is printed out.
    pointer_wrapper<int>    nullPointer;
    *nullPointer = 42;
    std::cout<<"Your number: " << *nullPointer;


    // ERROR:   Now we change the CheckingPolicy=NullChecking
    // This will print out the error message, before the segmentation-fault. 
    pointer_wrapper<int, NullChecking>    ptr;
    *ptr = 42;
    std::cout<<"Your number: " << *ptr;
}
```

**Note**
- The methods of policy classes <u>must be static, so that compiler can figure out at run-time. </u>
- Each of the policy classes are simple structs/classes without state that just implement a single static method.

<a name="crtp"></a>
## CRTP

- Curously Recurring Template Pattern
- Used for static polymorphism i.e. when we can create inheritance at compile-time.
- Used for injecting behaviour at compile-time.

```cpp
// Basic Idea
struct derived : public Base<derived>
{
    ....
}
```

Example implementation:

```cpp
template <class Derived>
struct Base
{
    void interface(){
        // cast this pointer to derived class type and call implementation
        static_cast<Derived*>(this)->implementation();
    }
}


struct Derived : public Base<Derived>
{
    void implementation();
}
```

#### Use-cases

##### 1.  Cloneable

```cpp
template <class Derived>
struct Cloneable
{
    Derived* 
    clone()
    {
        // create a new Drived type using the copy constructior.
        return new Derived( static_cast<Derived const&>(*this) );
    }
}

// usage
struct SomeExistingClass : public Cloneable<SomeExistingClass>
{
    ...
}

```

##### 2.  boost::enable_shared_from_this

Note how this example purely injects behaviour into our class without utilizing any information about the Derived type:

```cpp
template <class T>
struct enable_shared_from_this
{
    shared_ptr<T> 
    shared_from_this()
    {
        shared_ptr<T> p(weak_this_);
        return p;
    }

    // const version    
    shared_ptr<T const> 
    shared_from_this() const
    {
        shared_ptr<T const> p(weak_this_);
        return p;
    }

private:
    // weak pointer
    mutable weak_ptr<T> weak_this_;
}

```

<a name="typetraits"></a>
## Type Traits

Type traits are certain properties that we add to the template types to:
- query characteristics about template types.
- Note that template specialization is pattern matching. If the pattern does'nt match the compiler throws an error.

Examples

1.   **is_int**<T.>

```cpp
// types we are not interested in will have value = false
template <typename T>
struct is_int
{
    static const bool value = false;
}

// specialize the type we are interested in.
template <>
struct is_int<int>
{
    static const bool value = true;
}

// usage

cout<<  is_int<int>::value ;            // prints 1
cout<<  is_int<float>::value ;          // prints 0
cout<<  is_int<MyCustomType>::value;    // prints 0
```

So as you can see above that for any cutom-type I can use is_int<T>::value


2.  **is_same**<T,T>

    ```cpp

    template <typename T1, typename T2>
    struct is_same
    {
        static const bool value = false;
    }

    //specialize
    template <typename T>
    struct is_same<T,T>
    {
        static const bool value = true;
    }
    ```
3.  Standard Libary: C++11 <type_traits>
4.  Boost.TypeTraits
5.  Exercise:
        Write a type trait that will be true if the type is boost::shared_ptr<T>

    ```cpp

    template <typename T>
    struct is_sharedptr
    {
        static const bool value = false;
    }

    //specialize
    template <typename T>
    struct is_sharedptr<boost::shared_ptr<T>>
    {
        static const bool value = true;
    }
    ```

## Tag Dispatching

## SFINAE
- substitution failure is not an error

**std::enable_if<bool, class T = void>** : 
Can be used to disable one method/constructor completly if the first template parameter condition is not true.

e.g. sometimes we need the constructor to distinguish between integer and floating point types and not implicitly cast them.

```cpp
// Possible Implementation
template<bool B, class T = void>
struct enable_if {};
 
 // true case specialized 
template<class T>
struct enable_if<true, T> { typedef T type; };
```
So the type only exists when condition is true. 
If the compiler encounters the false case, it will discard generation of that function/class template.

See also [docs](https://en.cppreference.com/w/cpp/types/enable_if).

Example Usage:

```cpp
// Given some class value 
class value;

// constructor only enabled for float or double types
template <typename T>
value(T val, 
    typename enable_if<
                std::is_floating_point<T>::value, T
            >::type* = 0) 
    : base_type( double_t(val))
){ }

// constructor only enabled for int or enum types
template <typename T>
value(T val,     
    typename enable_if<
            boost::mpl::or_< 
                std::is_integral<Integer>::value, 
                is_enum<T> 
            >, T>::type* = 0) 
    : base_type( int_t(val))
){ }
```

__NOTE:__ type* above means a pointer. It is passed as a second argument to the original constructor of the value() and this second argument is set to default zero (T* = 0)

## Examples

### 1. Generic Point 

Imagine you have a 2D Point class defined in a library and you define a distance function using it.

```cpp
struct  myPoint
{
    double x;
    double y;
}

double
distance(mypoint const& a, mypoint const& b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;

    return std::sqrt(dx*dx + dy*dy);
}
```

Now Imagine you integrate a second library or define another custom point like below:

```cpp
struct  yourPoint
{
    double x;
    double y;
}
```
So you update the distance function such that it can use either of the point-types or even mix them while calculating distances between them. 
So you use templates to define a generic distance function that takes two point types:

```cpp
template <typename P1, typename P2>
double
distance(P1 const& a, P2 const& a)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;

    return std::sqrt(dx*dx + dy*dy);
}
```

The above assumed that the each of the point types satisfy the requirement that x,y coordinates can be accessed publically. 

Now imagine the situation where a third point type is defined such that it's interface is incompatible with other points: 

```cpp
struct  secretPoint
{
    double get_x();
    double get_y();
private: 
    double x,y;
}
```

Now you want to update the distance function to also cater for secretPoint above.  Some startegy like below could address the problem:

```cpp
// update distance function such that it has a generic get<i>(T)
template <typename P1, typename P2>
double
distance(P1 const& a, P2 const& a)
{
    double dx =  get<0>(a) - get<0>(b);
    double dy =  get<1>(a) - get<1>(b);

    return std::sqrt(dx*dx + dy*dy);
}
```
So how do we go about implementing this get<> method? <p>
We can use traists to specialize on each of the incompatible types (i.e. myPoint, SecretPoint etc.):

```cpp
namespace traits
{
    template <typename T, int D>
    struct access { };
}

namespace traits
{
    // specialize myPoint 
    
    // index i = 0
    template <>
    struct access <myPoint, 0>
    {
        static double 
        get( myPoint const& p)
        {
            return p.x;
        } 
    }

    // Same for index i = 1

    //----------------------
    // specialize secretPoint 
    
    // index i = 0
    template <>
    struct access <secretPoint, 0>
    {
        static double 
        get( secretPoint const& p)
        {
            return p.get_x();
        } 
    }

    // Same for index i = 1
}
```

This means that in the distance fucntion, the get<> method needs to be prefixed with **traits::access<T,i>**::get, like: 

```cpp
// update distance function such that it has a generic get<i>(T)
template <typename P1, typename P2>
double
distance(P1 const& a, P2 const& a)
{
    double dx =  traits::access<P1,0>::get(a) - traits::access<P2,0>::get(b);
    double dy =  traits::access<P1,1>::get(a) - traits::access<P2,1>::get(b);

    return std::sqrt(dx*dx + dy*dy);
}
```
This can be further improved, if we introduce a proxy function that does the prefixing for us. This way we can get our final inteded form for get():

```cpp
// add a proxy function to remove prefix.
template <int D, typename P>
inline double
get(P const& a)
{
    return traits::access<P,D>::get(a);
}
```

### 2. N-Dimensional Point
If p,q are points in n-dimensional space, then the distance function as given by Pythagores :

$ d(p,q) = \sqrt{ \sum_{i=1}^n (q_i - p_i)^2  } $

To implement this we borrow the idea of template recursion (as used in the Factorial example). Let's call the term inside the square-root as pythogras and create a function to calculate it:

```cpp
// add a proxy function to remove prefix.
template <typename P1, typename P2, int N>
struct pythagoras
{
    static double 
    apply(P1 const& a, P2 const& b)
    {
        double d = get<N-1>(a) - get<N-1>(b);
        // recurse
        return d*d + pythagoras<P1, P2, N-1>::apply(a,b);
    }
}

// specialize for N=0
template<typename P1, typename P2>
struct pythagoras<P1, P2, 0>
{
    static double 
    apply(P1 const& a, P2 const& b)
    {
        return 0;
    }
}
```

So the distance function should then look like:

```cpp
template<typename P1, typename P2>
double 
distance(P1 const& a, P2 const& b)
{
    // check that two point types have the same dimension.
    static_assert(dimension<P1>::value == dimension<P2>::value);

    constexpr int N = dimension<P1>::value;
    return std::sqrt(  pythagoras<P1, P2, N>::apply(a,b) );
}
```

Where dimension is just a type-trait of point type, implemented as follows:

```cpp

// step 1: define an empty struct, with no property for generic types
namespace traits
{
    template<typename P>
    struct dimension { }
}

// step 2: specialize ( for myPoint )

namespace traits
{
    template<>
    struct dimension<myPoint>
    { 
        static const int value = 2;
    };

// OR, using boost

    template<>
    struct dimension<myPoint> : boost::mpl::int_<2>
    {  };

}



```


## Factorial

```cpp
template <int N> 
struct Factorial
{
    static int const value = N * Factorial<N-1>::value;
};

template <>
struct Factorial<0>
{
    static int const value = 1;
};

// usage
Factorial<12>::value; 

// Note: This method only works for integer <= 12.
// Higher value than that gives an integer overflow error.
```


## Final Note: 

**Note** that in practise in metaprogramming we use three types of things:
1. value
2. types
3. apply
