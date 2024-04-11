#  Unique Pointer [std::unique_ptr]

## Table of Contents

- [Introduction](#unique-pointer-stdunique_ptr)
- [Important Methods](#important-methods)

- [Use Cases](#important-methods)
    - [Factory Method](#1-factory-method)
    - [PIMPL](#2-pimpl-idiom)
    - [RAII ](#2-pimpl-idiom)

- [Conversion to shared_ptr](#3-conversion-to-shared-pointers)


## Introduction

Bjourne Stroustrupp
: "*Release of resources must be guaranteed and implicit*"

**std::unique_ptr** guarantees that *delete* will be called for every *new*. <p> 
It uses [RAII](./RAII.md) pattern and the deleter is called automatically, when the pointer goes out of scope. This property of unique_ptr makes it ideal to implement general RAII using custom deleters for resources other than memory.

-   Automatically calls delete when out of scope.
-   **Exclusive ownership** 
-   Same size as raw pointer

It can be declared using any of the following forms:

```cpp
#include <memory>

{
    // 1 - with a Raw pointer
    std::unique_ptr<T> pointer(new T);

    // 2 - with std::make_unique<>
    auto pointer = std::make_unique<T>(...);  // pass arguments if any

    // 3 - with Custom deleter
    auto deleter = [](T* raw){ // };
    std::unique_ptr<T, decltype(deleter)> pointer(nullptr, deleter); 

} // memory freed
```

### Prohibitions

- **Copying**  to another unique_ptr is not allowed.

    ```cpp
    std::unique_ptr<T> a = std::unique_ptr<T>(new T);
    std::unique_ptr<T> b = nullptr;

    b = a;      // compiler-error
    ```

- **Moving** from another pointer is allowed. This transfers ownership and sets the source pointer to nullptr.

    ```cpp
    std::unique_ptr<T> a = std::unique_ptr<T>(new T);
    std::unique_ptr<T> b = std::move(a);    
    
    // a = nullptr 
    ```

You may ask why?
The main goal of unique_ptr is to release resource only once along the entire code path. So copying is not allowed as this raises the question which pointer should call the delete? 

## Important Methods
- __get()__ :  gets a copy of the internally managed pointer or nullptr if no pointer is being managed.

- __reset( T* newPtr)__ : replaces the internal pointer with the newPtr and calls __delete__ on the old managed pointer. 

    ```cpp
    std::unique_ptr<T> a = std::unique_ptr<T>(new T);
    auto ptr = std::make_unique<int>(100);

    // Three ways to modify the internal value of the
    // managed object.

    // 1. Raw-pointer
    *(ptr.get()) = 1;
    
    // 2. De-reference operator
    *ptr = 2;

    // 3. reset(....)
    ptr.reset(new int{3});   // will call delete on old pointer
    ```

- **release()**:  This causes the unique_ptr to release ownership of the managed object and return the pointer. From this point onwwards, the call to get() will return nullptr. It is now the responisibility of the caller to take ownership of the returned pointer and call delete on it (e.g. by using get_deleter() ). 
    ```cpp
    std::unique_ptr<T> ptr(new T());
    legacy_api(ptr.release());
    assert(ptr == nullptr);
    ```

## Use Cases 

We will discuss the following use-cases of the unique_ptr:
1.  Factory Method
2. Pimpl Idiom
3. Custom RAII class
4. Cast to shared_ptr

### 1. Factory Method
A factory method usually: 
1.  Creates an object on the heap and return the pointer to the caller. 
2.  Expects the caller to take ownership of the pointer and handle it's deletion.

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
- intially the pShape pointer is initialized with nullptr
-   **reset** method is used to reset the internal raw-pointer of the unique_ptr with a call to **new**. 
- The base class Shape will require a virtual destructor for this pattern to work.
- When using the custom deleter the size of the unique_ptr will depend on the size of the lambda. It can grow bigger than the raw-pointer depending upon how much state is being stored in the lambda.


### 2. Pimpl Idiom

Pimpl Idiom implementation is another popular use-case of unique_ptr.

### 3. Custom RAII class 

std::unique_ptr can be used to create any kind of custom RAII class  to mange other non-pointer resources like files, mutex-locks, etc.

Just acquire the resource in the constructor and provide a custom deleter to the unique_pointer. 

```cpp
class Resource{

    // constructor
    Resource() 
    {
        //  acquire resource here
    }

    ~Resource
    {
        delete 
    }


}
```

### 4. Conversion to Shared-Pointers

Another attractive feature of unqiue_ptr is that it is convertible to a shared-pointer:

```cpp
std::shared_ptr<T> sp = factoryMethod<T>(args);
```
This is the key reason for why Factory Methods prefer returning a unique_ptr. The caller can decide wether to use <u>exclusive ownership semantics</u> for the returned object or <u>shared ownership semantics.</u> 

