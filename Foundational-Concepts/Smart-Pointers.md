# Smart Pointers

Table of Contents

- [ Raw Pointers ](#raw-pointers-t) 
- [Smart Pointers](#smart-pointers-1)
    - [std::unique_ptr](#unique-pointer-stdunique_ptr)
    - [std::shared_ptr](#shared-pointers-stdshared_ptr)
        - [Control Block]
        - [Control Block]
    - [std::weak_ptr](#weak-pointers)
- [Specifying Intent with Smart-Pointer Paranaters]

<a name="raw"></a>
### Raw Pointers:  T*

A pointer is a type of variable that:

- Stores the **address** of an object in memory. 
- __Lifetime__: It's lifetime isn't controlled by the encapsulating object. The pointer variable can go out of scope while the memory resource it is pointing to will still remain alive until explicilty cleaned up.
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

## Smart Pointers

These are just wrappers around old raw pointers. <p>
- They add additional functionalities to raw pointers e.g. automatic resource cleanup, reference-couting etc. 
- Restrict undesired operations .
- Their API must conform to the original syntax of the raw pointers. 

    They must support * and -> operators just like raw pointers.

    They must also support increment ++ and decrements --


#### Exclusive vs Shared Ownership model
Currently two approaches are common amongst smart-pointers handling of dynamic memory. 

__Exclusive__ :
Either a pointer can exclusively own the memory it points to i.e. no other pointer can even point to it. <u>Copying this pointer is not allowed</u> and it can <u>only be passed on to another pointer with std::move().</u> 

__Shared__ :
Or it can share the memory reference with other pointers 

##  Unique Pointer [std::unique_ptr]

See [document: unique_ptr.md](Unique_ptr.md)

###  Shared Pointers [std::shared_ptr] 

###  Weak Pointers


### Specifying Intent with smart-pointer parameters 

Use smart pointers as paramters only to explicitly express lifetime semantics. [[R.30]](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#r30-take-smart-pointers-as-parameters-only-to-explicitly-express-lifetime-semantics)

Passing smart-pointers as paramaters transfers or shares ownership, and should only be used for this intent. [[F7]](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#f7-for-general-use-take-t-or-t-arguments-rather-than-smart-pointers)

Let's discuss what intent is expressed by different smart pointer parameters:

- **unique_ptr< T >**   <p>
Express the intent that the function should take ownership of the pointer, or in other words your passing ownership of the object.

```cpp
void sink(unique_ptr<widget>); // takes ownership of the widget

// The only valid way to use this function will be with an std::move() or an r-value. Pass-by-value will give a compile error since the copy-constructor is deleted.

// Valid uses:
//1. 
auto ptr = std::make_unique<Widget>();
sink(std::move(ptr));
//2.
sink(std::make_unique<Widget>());
sink(std::unique_ptr<Widget>(new Widget));

// Error: Copy constructor is implicitly deleted ...
auto ptr = std::make_unique<Widget>();
sink(ptr); 
```

- **unique_ptr< T >&** <p>
Express intent that the function **should reseat** the pointer. Reseat means “making a pointer refer to a different object”.  

```cpp
void function(unique_ptr<widget>& ptr) // "will" or "might" reseat pointer
{
    // change the value through the managed pointer
    *(ptr->get()).widget_width = newWidth;

    // reset the widget entirely
    ptr.reset(new Widget());
}
```
if the function does not call reset() or assigns a new value to the pointer, give a warning and suggest to use just T* or T& instead of unique_ptr<T>&

- **const unique_ptr< T >&** <p>
Never use this. Use T& reference or T* pointer instead.


- **shared_ptr< T >**

- **shared_ptr< T >&**
- **const shared_ptr< T >&**


```cpp
void share(shared_ptr<widget>);            // share -- "will" retain refcount

void reseat(shared_ptr<widget>&);          // "might" reseat ptr

void may_share(const shared_ptr<widget>&); // "might" retain refcount
```

- __Rule #1__ <p>
A function that does not alter owner-ship semantcis should use T* or T& 

## Non-Owning pointer to arrays
Use a std::span (C++20) or gsl::span

## Const-Correctness <p>
https://isocpp.org/wiki/faq/const-correctness 
