#include <iostream>
#include <string>
#include <functional>

// Just a normal function that returns an int
int length(){
   return 10;
}

// Templated function that could return anything: int, float, double etc.
template <typename T>
T square(T len){
   return len*len;
}

// a function that takes square(T) function-ptr as argument
template <typename T>
T cube1( T (*square)(T), T len )
{
   return square(len) * len;
}

// function-ptr typedef
template <typename T>
using funcptr = T(*)(T);

template <typename T>
T cube2( funcptr<T> func, T w )
{
   return func(w) * w;
}

template <typename W> 
W cube3( std::function<W(W)> func, W w )
{ 
   return func(w) * w;
}


int main(int argc, const char * argv[]) {
    
   // declare a function pointer for someFunc
   int (*fptrLength)();          // fptrLength is the ptr to any function that returns an int and takes no parameters
   fptrLength = &length; 

   //int (*funcPtrGetArea)(int) = {&getArea};
   float (*fPtrSquare)(float) = {&square};

   // Address of the function in memory
   std::cout<< "\n" <<reinterpret_cast<void*>(length) <<"\n";

   // call length() through function-pointer
   std::cout<< "\n" << fptrLength() <<"\n";

   std::cout<< "\n" << fPtrSquare(11.0) <<"\n";
   std::cout<< "\n" << cube1( fPtrSquare, 0.2f ) <<"\n";
   std::cout<< "\n" << cube2( fPtrSquare, 0.3f ) <<"\n";

   // passing std::function as parameter
   std::function<float(float)> fptrFloat = [](float a)->float{return a*a;};
   std::function<double(double)> fptrDouble = [](double a)->double{return a*a;};
   std::cout<< "\nCube3: " << cube3( fptrFloat, 0.3f ) <<"\n";
   std::cout<< "\nCube3: " << cube3( fptrDouble, 0.4d ) <<"\n";
   //std::cout<< "\nCube3: " << cube3( fPtrSquare, 0.2f ) <<"\n";

   // int operation (int x, int y,int (*function)(int,int)){return function(x,y);}
   // int operation2(int x, int y,std::function<int(int, int)> function){return function(x,y);}


   //---------   
   // Lambda: 
   //---------
   // What compiler does behind the scenes, when it sees a Lambda: 
   //    1. creates a Functor object with overloaded operator () 
   //    2. captures the local variables used by Lambda as memebers of the Functor object, as specified by the capture-mode. 
   auto func = [] () { std::cout << "Hello world - from the Lambda-Side\n"; };
   func();

   [] () -> int { return 1; };      // C++11 optional return syntax
   [] () -> double { return 1; };   // C++11 optional return syntax

   // Lambda Capture Modes
   // []	         Capture nothing (or, a scorched earth strategy?)
   // [&]	      Capture any referenced variable by reference
   // [=]	      Capture any referenced variable by making a copy
   // [=, &foo]	Capture any referenced variable by making a copy, but capture variable foo by reference
   // [bar]	      Capture bar by making a copy; don't copy anything else
   // [this]	   Capture the this pointer of the enclosing class



   return 0;
}
