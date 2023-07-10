#include <iostream>
#include <memory>

/*

   // std::unique_ptr< T > 

   Summary:
   - By default the std::unique_ptr is the same size as corresponding raw-pointer.
   - Exclusive Ownership: 
     It always owns what it points to. 
     This means that, if non-NULL, the memory will be destroyed/deleted when 
     std::unique_ptr will go out of scope. e.g. :
     
     {
        std::unique_ptr<int> a = std::make_unique<int>( 10 );
     } // memory destroyed here

   - Copy is not allowed:
      std::unique_ptr<int> a = std::make_unique<int>( 10 );
      std::unique_ptr<int> b = a;   // ERROR

   - Moveable
        auto personA = std::make_unique< Person >();
        std::unique_ptr< Person > personB = std::unique_ptr(std::move(personA));


   Properties:       
   - Non-Copyable
   - Moveable
   - Custom Deleters
   - Factory-Methods return type.


   // Shared Pointers
   - Control Block for reference count


   // Weak Pointers

*/


int main(int argc, const char * argv[]) {   

   struct Person{
      Person(int v):val(v)    {std::cout<<"\n Person("<<this->val<<")";}
      ~Person()               {std::cout<<"\n ~Person(); \n\n";}
            
      int val;
   };


   // Moving a Unique pointer
   {
      auto A = std::make_unique<Person>(10);          // Prints: Person(10)
      auto B = std::unique_ptr(std::move(A));         

      std::cout << "\n B->val: "<< B->val;            // Prints: B->p 10
      
      //ERROR: uncomment below line for compiler error
      // auto C = B;
   }                                                  // Prints: ~Person()

   


   return 0;
}
