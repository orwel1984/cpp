#include <iostream>
#include <vector>
#include <algorithm>

/*
    std::vector represents a "contiguous array" of data elements, allocated on the heap instead of the stack. 
    This allows us to resize the array dynamically -- compared to std::array where the size of the array is fixed. 
    (as std::array is simply a wrapper around normal C-style array [] on "Stack")

    The std::vector::size():        gives the total elements contained in the vector.    
    
    The std::vector::capacity():    represents the total number of elements that the vector currently 
                                    can hold, before it needs to reallocate the array on heap.

    Thus std::vector provides a resizeable contiguous array.
    
    Contiguous arrays are efficient to traverse as they provide good cache locality.
    With a linkedlist traversing from one pointer to another leads to accessing 
    different parts of the memory.

    Reallocation: 
    --------------
    Whenever the size() == capacity() and a new element needs to be inserted into the 
    vector, then a new array is reallocated and old one destroyed. All elements are then
    copied into the new memory location. Thus, this is a time consuming operation. 


    Safe Access    
    -------------
    std::vector provides following methods to access the elements in the array:

    [] operator:        vector[i] will return the i-th element in the array.
                        This is an un-safe access as no bound-checking is done.
                        If you access an element [i] where i >= size() then 
                        this could lead to dangerous undefined behaviour. 
                        However, this is a fast-access method with no additional overhead.

    at(i):              This is a safe way to access the elements as bounds checking will
                        be performed. This could throw an 'std::out_of_range' Exception.



    push_back vs emplace_back :   
    ---------------------------
    The most common method used to insert elements in the vector is the push_back().
    See the main() function below for details on how push_back() differs from emplace_back();

    NOTES:
    -   std::vector< T* > and std::vector< std::unique_ptr<T> > is possible .
        but std::vector< T& > is ill-formed and should not be used.

    -   std::reference_wrapper is used to create a std::vector of references.

    -   std::vector<bool> is a special case. It is not an STL container and should be 
        avoided (Scott Meyers's book Effective STL). It stores bits of data rather than arrays of bools.

*/

struct Point2D
{
    float x,y;
};

int main(){

    // using uniform intialisation with {}
    std::vector<int> v{1, 2, 3, 2, 5, 2, 6, 2, 4, 8};

    std::vector<Point2D> points {
                            {1,1},
                            {2,2},
                            {3,3},
                            {4,4},
                        };

    std::cout<<"\nSize:"<<points.size();
    std::cout<<"\nCapacity:"<<points.capacity();

    // SAFE-ACCESS TEST
    // Let's access a value outside the range of vector using vector.at()    
    try 
    {
        auto& point = points.at(points.size() + 1);
        
        std::cout   << "\n\nValue: " 
                    <<  point.x << '\n';
    } 
    catch (const std::out_of_range &e) 
    {        
        std::cout   << "\n\nException, out of range memory access:\n" 
                    << e.what();
    }

    // UNSAFE-ACCESS TEST
    // Let's access a value outside the range of vector using []
    auto& point = points[ points.size()+1 ];
    std::cout   << "\n\nUnsafe-value: " 
                <<  point.x << '\n';



    /*
    push_back vs emplace_back    
    -------------------------
    The push_back() function has the following overloads, based on if you pass
    an L-value or an R-value (e.g. a temporary or by using std::move() )
    
    void push_back( const T& value );           (until C++20)
    void push_back( T&& value );                (since C++11)
    
    NOTE: since C++20 above have constexpr overloads https://en.cppreference.com/w/cpp/container/vector/push_back
    
    
    EMPLACE_BACK():
    The emplace_back() function is defined using the following overloads:       
    
    template< class... Args >
    void                 emplace_back( Args&&... args );     (since C++11, until C++17)
    reference            emplace_back( Args&&... args );     (since C++17, until C++20)
    constexpr reference  emplace_back( Args&&... args );

    It std::forwards the arguments passed in to the actual constructor of the object. 
    See variadic functions https://en.cppreference.com/w/c/variadic

    */

    // we need to see how objects are copied or moved when using emplace_back vs push_back. 
    struct S{
        // a simple class which does'nt have any "move-able data".

        S():x(0),y(0)   {std::cout<<"\nS(0,0)";}
        S(S const & s)     {std::cout<<"\nS(const S&)"; x = s.x; y=s.y;}    // copy-const
        S(S && s)          {std::cout<<"\nS(S&&)"; x = s.x; y=s.y; } // move-const   
        ~S()            {std::cout<<"\n~S()";}           // destructor
        
        S& operator=(const S& other)  {std::cout<<"\nOperator="; return *this;}
        S& operator=(S&& other)       {std::cout<<"\nOperator="; return *this;}

        // additional custom constructors with parameters
        S(int x):x(x),y(0) {std::cout<<"\nS(x)";}
        S(int x, int y):x(x),y(y)    {std::cout<<"\nS(x,y)";}

        // members
        int x;
        int y;
    };


    std::cout<<"\n\n-PUSH_BACK test with L-Value or R-Value";
    {
        std::vector<S> vect;
        S l_Value = {1,1};
        //vect.push_back( l_Value );     
                
        // Following statements call a move constructor instead of copy-constructor 
        // but still creates two objects as above. Because S does'nt have any internal data which 
        // can take advantage of move constructor. It's just a bunch of int's.
        // But if it had another vector or list of items, it could be faster.

        // Uncomment them to test.

        vect.push_back( std::move(l_Value) );
        // vect.push_back({1,2});   
        // vect.push_back( S(1) );     
    }

    std::cout<<"\n\n-EMPLACE_BACK test with arguments (CORRECT WAY)";
    {
        std::vector<S> vect;
        vect.emplace_back( 1,2 );   // passes arguments of the constructor of S, 
                                    // instead of an object of S.
                                    // This creates an object in-place inside the vector.

        // WRONG WAY of using Emplace_back.
        // 
        // The following statements are equivalent to their push_back() counterparts
        // and give no extra benefit of using emplace_back.
        //
        // S l_Value;
        // vect.emplace_back( l_Value );
        // vect.emplace_back( std::move(l_Value) );
        // vect.emplace_back( S() );
    }


    std::cout<<"\n\nFinito\n\n";

    return 0; 
}