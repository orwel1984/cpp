#include <iostream>
#include <vector>

/*
*************************
  1. Inheritance:
*************************

- Provides a way to reuse the definition of a Base class.

      class Base { }

           -------------------------------------------------------------
           Base Class            -------->         Child/Derived Class
           -------------------------------------------------------------           
Public Inheritance :            class Child : public Base {} 
        Public    Methods/Members  -------> Public    Methods/Members
        Protected Methods/Members  -------> Protected Methods/Members
        Private   Methods/Members  -------> Unavailable - (accessible indirectly through public/protected methods)  

Protected Inheritance :         class Child : protected Base {}
        Public   Methods/Members  -------> Protected    
        Protected Methods/Members  -------> Protected 

Private Inheritance −           class Child : private Base {}
        Public   Methods/Members  -------> Private    
        Protected Methods/Members  -------> Private 

************************************
2. Virtual "Functions" & Polymorphism:  (see also virtual, override keywords) 
************************************

- Functions marked "virtual" in Base can be "overriden" by a Child class to provide 
  their own specialized implementation.
    - Use "virtual" keyword in Base class 
    - Use "override" keyword in Child class (C++11)
 
*********************
3. V-Table & v_ptr: 
*********************

- Non-virtual member functions are resolved statically (at compile-time) 
  - e.g. Base * b = new Child()
        - any call to a non-virtual method 
          b.func() will be mapped to "Base::func()" at "compile-time". 

- Virtual member functions are resolved dynamically (at run-time) 
  based on the actual type of the object in memory. 
  This is called “dynamic binding.”
  - e.g. Base * b = new Child()
        - any call to a virtual method 
        - b.func() will be mapped to "Child::func()" at "run-time".
 
- V-pointer:
  If a class has one or more virtual functions, the compiler puts a hidden pointer as a member-variable
  in the top level Base class called a “virtual-pointer” or “v-pointer.”

- V-Table:
  Then, every class that uses or inherits virtual functions, 
  the compiler creates a v-table or "virtual-table" for each class.  
  This table is simply a static array of function-pointers, where each pointer points to 
  the implementation of virtual functions that can be called by objects of this class. 

  The Child::v_ptr member variable then points to the v-table of Child class. 
  The Base::v_ptr member variable then points to the v-table of Base class. 
  
*****************************************
4. Virtual Destructor: 
*****************************************
- If ~Base() is not decalred virtual, then for any pointer of type Base* e.g. 
    Base * base = new Child();    
  here 'base' will be mapped to ~Base() on destruction at compile-time. 
  instead of ~Child();

*******************************************
5. Vritual "Inheritance" & Diamond-Problem: 
*******************************************

        class Base
            /   \     
           /     \
          /       \
      Child-1     Child-2
         \        /
          \      /
           \    /
        Grand-Child

  class Base{ func(){} }
  class Child1: public Base{ }
  class Child2: public Base{ }
  class GrandChild: public Child1, public Child2 {}

  - In the case above the Grandchild will inherit two copies of func(): Child1::func() & Child-2::func()
    This will create ambiguity for the compiler 

  - Virtual Inheritance: 

    class Base{ func(){} }
    class Child1: virtual public Base{ }
    class Child2: virtual public Base{ }
    class GrandChild: public Child1, public Child2 {}

    See the use of "virtual" keyword before. 
    This will tell the compiler to create only one copy of Base() class in the inherited children.

*/

/*
***********************************************
  SAMPLE CODE
***********************************************
*/

class Base {
  public:
            void F1()   { print("f1()"); }      // Non-Virtual
    virtual void F2()   { print("f2()"); }      // Virtual
    virtual void F3() = 0;                      // Pure Virtual - no implementation
 
  public :    
    // Destructor:    
    ~Base(){ print("~Base()"); }                // Wrong: must be virtual if this class is to be inherited.
    // virtual ~Base(){ print("~Base()"); }     // OK:    virtual
    
 protected:
    // helper function to print something - also Non-Virtual
    void print(const char* message){
        std::cout<<"\n"<<message;
    }    
 };

class Child : public Base {
  public:
    // Pure-Virtual: must "override" F3() for  Child is to be instantiated.
    void F3() override  { print("Child::f3()"); }

    // no F1: fine, Base::f1 will be inherited
    // no F2: fine, Base::f2 will be inherited if Not overriden
    void F2() override  { print("f2()"); }
    ~Child() { print("~Child()"); }
};
 

int main() {

    {   // define an empty-scope to test call to destructor

        // Base b;      // ERROR :  F3() is pure-virtual, not overridden

        Child c;        // OK    :  Child::F3() exists
        c.F1();         // OK    :  Base::F1 will be called.
        c.F2();         // OK    :  Child::F2 will be called.      

    }   // ~Child() destructor will get called when c goes out of scope.
        // ~Child() will give a call to ~Base()


    Base* base = new Child();           
    delete base;                //  Runtime Error:  Undefined behaviour if ~Base() is not virtual.
                                //                  It will not call ~Child() since base is of Base* type.

    /*
    ***********************************************
    Best Practices - C++ 11
    ***********************************************
    
    1.  Always use "override" keyword in Child classes for virtual functions.

    */

    return 0;
}