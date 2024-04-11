#  Shared Pointer [std::shared_ptr]

## Table of Contents

- [Introduction](#introduction)


## Introduction

std::shared_ptr implements <u>shared-ownership</u> semantics. This means that all the pointers pointing to the resource, collaborate together to ensure the release of resources when it is no longer needed by anyone. 

When std::shared_ptr goes out of scope, it checks the reference-count (i.e. the total no. of pointers pointing to the resource), to see if it is the last one. If so, it calls delete (or custom deleter) on the managed raw-pointer.

### Cost of Reference Counting

-   Reference count memory <u>must be dynamically</u> created.
- Incrementing/decrementing a reference count must be atomic.
- There is also a virtual function involved, which is used to ensure that the pointed-to-object is properly destroyed. Hence, the cost includes the machinery for virtual functions.

- works best when default deleter, default allocator with std::make_shared is used. In this case the 

- once any kind of ownership is passed to std::shared_ptr, you cannot reclaim it back to let's say a unique_ptr. It will now call a deleter on the resource.

### Control Block

- always created with a call to std::make_shared()
- always created when constructed from a unique_ptr or a raw pointer.
- not created when created from an existing std::shared_ptr or std::weak_ptr

Note: constructing multiple shared_ptrs from a single raw-pointer gives undefined-behaviour and is dangerous, since this will create multiple control blocks and also call delete multiple times. So avoid passing raw-pointers to the shared_ptr constructors.

Not possible to use std::make_shared with a custom-deleter. In that case pass the result of *new* directly instead of going through a raw-pointer variable.

#### Control Block Contains:
- Reference-Count
- Weak Count
- Custom Deleter (if any)
- other data (allocator?)


#### std::enable_shared_from_this<T> & shared_from_this()
- private constructor essential

### Important Methods

- reset
- get()
- use_count:  <u>Never</u> use this, specially in multi-threaded environements. 

Note: Unlike unique_ptr<T> there is no release( ) method, because shared_ptr can never tell if the memory is being owned by someone else and call delete on it.


### Aliasing Constructor & Type Erasure

The aliasing constructor: <p>
```cpp
template< class Y >
shared_ptr( const shared_ptr<Y>& r, element_type* ptr ) noexcept;
```

Constructs a shared_ptr which shares ownership information with the initial value of r, but holds an unrelated and unmanaged pointer ptr. If this shared_ptr is the last of the group to go out of scope, it will call the stored deleter for the object originally managed by r. However, calling get() on this shared_ptr will always return a copy of ptr. It is the responsibility of the programmer to make sure that this ptr remains valid as long as this shared_ptr exists, such as in the typical use cases where ptr is a member of the object managed by r or is an alias (e.g., downcast) of r.get() For the second overload taking an rvalue, r is empty and r.get() == nullptr after the call.(since C++20)