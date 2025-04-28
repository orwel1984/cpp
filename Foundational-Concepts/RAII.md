# RAII - Resource Acquisition is Initialization

Table of Contents

- [ Resource ](#resource) 
    - [ Common Problems ](#common-problems-when-using-resources)
- [ Object Lifetime ](#c-objects-lifetimes)
 - [ Examples of RAII Classes ](#example-raii-classes-in-standard-c)
    - [Lock Guard](#1-stdlock_guard)
    - [Unique Ptr](#4-stdunique_ptr)
    - [File Lock](#6-stdfstream)
    - [Threads](#3-stdjthread)
 - [ Custom RAII Class ](#implementing-raii-classes)


## Resource

Definition
:   A resource is some facility or concept that you gain access to by some sort of **acquire** and **release** pair of operations.

Following table shows a list of common resources in C++, along with their acquire and release operations.

|   **Resource**   |           Acquire          |            Release           |
|:----------------:|:--------------------------:|:----------------------------:|
|   **_Memory_**   |       auto p = new T       |           delete p           |
| **_POSIX File_** |   fp = fopen("name", "r")  |          fclose(fp)          |
|   **_Threads_**  |   pthread_create(&p, ...)  |        pthread_join(p)       |
|   **_Mutexes_**  | pthread_mutex_lock(&mutex) | pthread_mutex_unlock(&mutex) |


### Common Problems when using Resources

- Leaking resource
- Use-after-Dispose
- Double dispose

## Object's Lifetime
C++ objects have a well defined beginning and end. These points in object's lifecycle have code that can be automatically executed by the language: Constructors & Destructors


## So What is RAII

This is the idiom where we <u>acquire the resource in the constructor </u> of the object and we <u>dispose the resource in the destructor</u>.

### Ownership
The concept of ownership is coupled with the idea of disposing a resource.  An RAII class is the owner of it's resource.

### Example RAII classes in standard C++

#### 1. std::lock_guard

```cpp
{
    std::lock_guard lock(someMutex);    //acquire
    
    // do something exclusive
    // ... 

}  //  dispose 

```

#### 2. std::unique_lock


#### 3. std::jthread
Joins the thread automatically when goes out of scope.

#### 4. std::unique_ptr

#### 5. std::shared_ptr
#### 6. std::fstream

### Implementing RAII classes

Some design choices that must be considered when implementing your own RAII classes. You must ask the following question about the resource you want to manage: 

- Copyable?
- Moveable?
- Default Constructor

## Rule of Zero

The rule of zero states that if your class has member variables that are just based on std::* RAII based containers (std::vector,  std::unique_ptr, etc.. ), then you should let the compiler generate all special functions for you (No need to explicitily decalre any custom constructor/destoructors/copy/move-assignments).
