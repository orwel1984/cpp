# Smart Pointers

###  Raw Pointers  T*

A pointer is a type of variable that:

- Stores the **address** of an object in memory. 
- *Lifetime*: It's lifetime isn't controlled by the encapsulating object.
- It can be assigned the address of another pointer or non-pointer variable, nullptr or contain some random data if unassigned.
- *Owning-Pointers*: <p>
When a program allocates an object on the *heap* in memory, it receives the address of that object in the form of a pointer. Such pointers are called *owning-pointers*. e.g. the call to **new** operator in C++ or **malloc** in C (which in turn calls the linux **brk()** and **sbrk()**  to increase the size of data-segment memory allotted to the process). 
- *Free Memory*: <p>
An owning pointer (or a copy of it) must be used to explicitly free the heap-allocated object when it's no longer needed. Memory allocated using **new** must be followed by a corresponding call to *delete* (or *delete[]*).  
- *Memory Leak*: <p>
Failure to free the memory results in a **memory leak**, and renders that memory location unavailable to any other program on the machine.
- *Void Pointers*: <p>
Void pointers are special kind of raw pointers that do not have type information. This means that incrementing and decrementing the pointer is not possible without knowing the underlying type.


Some problems with Raw pointers:

1.  Does T* points to an object or array?
2.  Should you **delete** it after use or keep it?
3.  *delete* or *delete [ ]* what to use?
4.  Did you *delete* the pointer only once along every path of code?
5.  Is the pointer dangling and already deleted?

#  Smart Pointers

These are just wrappers around raw pointers. <p>

Syntax-wise, they behave exactly like raw pointers, but solve issues with the raw pointers discussed above.

They prohibit some actions on raw-pointers, while automate other actions.

##  Unique Pointer [std::unique_ptr]

Addresses the problem of calling delete after new. <p>
It can be declared using any of the following forms:

```cpp
// 1 - with a Raw pointer
std::unique_ptr<T> pointer = std::unique_ptr<T>(new T);

// 2 - with Arguments
auto pointer = std::make_unique<T>(...);  // pass arguments if any

// 3 - with Custom deleter
auto deleter = [](T* raw){ // };
std::unique_ptr<T, decltype(deleter)> pointer(nullptr, deleter); 

```

-   Automatically calls delete when out of scope
-   **Exclusive ownership** of the object i.e. it won't allow copying the value, only moving. 
-   Same size as raw pointer

#### Prohibitions:
Copying one unique-pointer to another is now allowed.

```cpp
std::unique_ptr<T> a = std::unique_ptr<T>(new T);
std::unique_ptr<T> b = nullptr;

b = a;      // compiler-error
```

Moving from a source pointer to destination pointer transfers ownership and sets the source pointer to nullptr.

```cpp
std::unique_ptr<T> a = std::unique_ptr<T>(new T);
std::unique_ptr<T> b = std::move(a);    // a is now nullptr after move 
```

You may ask why?
This is the only way to ensure that across all the call chains and pointer exchanges, deletion happens only once.

#### Use Cases 

##### 1. Factory Method
A factory method usually: 
1.  Creates an object on the heap and return the pointer to the caller. 
2.  Excpects the caller to take ownership of the pointer and handle it's deletion.

This is a perfect case for a unique_ptr. <p>
However, there are some things to take care of, since a factory method usually involves polymorphism when creating objects.

```cpp
// consider the product heirarchy
class Shape {
    virtual ~Shape() = default;
}

class Circle : public Shape { }
class Square : public Shape { }
class Rectangle : public Shape { }

// custom deleter - always take raw pointer to the base class
auto deleter = [](Shape* rawPtr){ 
                            //... do some logging etc.
                            delete rawPtr;
                    };

template<typename... Ts>
std::unique_ptr<Shape, decltype(deleter)>
factoryMethod(Ts&&... params)
{
    std::unique_ptr<Shape, decltype(deleter)> pShape(nullptr, deleter);

    if( /*should create a circle ( params)*/ )
    {
        pShape.reset( new Circle(std::forward<Ts>(params)));
    }
    else if( /*should create a Square ( params)*/ )
    {
        pShape.reset( new Square(std::forward<Ts>(params)));
    }
    else if( /*should create a Rectangle ( params)*/ )
    {
        pShape.reset( new Rectangle(std::forward<Ts>(params)));
    }    

    return pShape;
}
```

**Note:**
-   custom deleter requires <u>a raw pointer to the Base class </u> and will call **delete** or **delete[ ]** on it. 
-   **reset** method is used to reset the internal raw-pointer of the unique_ptr with a call to **new**. 
- intially the pShape pointer is initialized with nullptr
- The base class Shape will require a virtual destructor for this pattern to work.
- When using the custom deleter the size of the unique_ptr will depend on the size of the lambda. It can grow bigger than the raw-pointer depending upon how much state is being stored in the lambda.


##### 2. Pimpl Idiom

Pimpl Idiom implementation is another popular use-case of unique_ptr.

##### 3. Conversion to Shared-Pointers

Another attractive feature of unqiue_ptr is that it is convertible to a shared-pointer:

```cpp
std::shared_ptr<T> sp = factoryMethod<T>(args);
```
This is the key reason for why Factory Methods prefer returning a unique_ptr. The caller can decide wether to use <u>exclusive ownership semantics</u> for the returned object or <u>shared ownership semantics.</u> 

###  Shared Pointers [std::shared_ptr] 


###  Weak Pointers


