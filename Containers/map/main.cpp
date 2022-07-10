#include <iostream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>

/*

std::map 

Stores values in a key/value pair.

Comes in two varieties.

1. Sorted (std::map) & UnSorted (std::unordered_map)- by keys
2. Single-Key and Multiple-Keys

std::map 
template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T> >
> class map;

- std::map is a "sorted" container that contains key-value pairs with unique keys. 
- Search, removal, and insertion operations have logarithmic complexity O(log N). 
- Keys are sorted by using the comparison function Compare. 
- Maps are usually implemented as red-black trees.
- NOTE: there is no HASH function in this container, it's not a HASH-MAP

std::unordered_map 
template<
    class Key,
    class T,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>,
    class Allocator = std::allocator< std::pair<const Key, T> >
> class unordered_map;

- Notice above that std::unordered_map differes from std::map with the presence of 
  HASH policy class defaulted to std::hash()
- Notice that default Allocator policy uses std::allocator() to create std::pair<const Key,T>

HASH-FUNCTION:
--------------
To choose an appropriate key for a very large dataset, we implement a function that maps values 
in the dataset to an integer in the desired "range". 
We choose the range so that the final array will have a feasible size (let's say some no. N)
This function is called a hash function. 
e.g. 
The simplest hash-function for integers is the modulo function (denoted by %), 
which divides the element by a specified integer (N) and returns the remainder. 
So, we'll simply have an array of size N.
The number that's obtained by applying the hash-function is called the "hash-value".

HASH-Collisions:
When multiple keys have the same hash value, this is called a hash-collision.
To resolve this problem we can use a no. of ways:
1. Close Addressing – Chaining:  This is one way we can retain both values. 
                                In this method, instead of storing a single key in the hash table, 
                                we'll store a linked list for each index. 

2. Linear & Quadratic Probing: 
3. Perfect Hashing – Cuckoo Hashing: 


Complexity: 
--------------

Access: 
LookUp:


*/

int main()
{
    // Note: braced initailization syntax
    std::map< std::string, int> contacts{  
                                {"John",    15456}, 
                                {"Ali",     10983}, 
                                {"Zebra",  45615}, 
                                {"Heckle",  45615}, 
                                {"Jackel",  43135}, 
                                {"Jackel",  678697}, 
                            };

    // elements will output sorted as sorted pairs and 
    // duplicate key such as the last "Jackel" will be ignored
    std::cout<<std::endl;
    for(auto contact:   contacts){
        std::cout<< contact.first << " , " << contact.second <<std::endl;
    }



    // Note: braced initailization syntax
    std::unordered_multimap< char, int> charPositionMap{  
                                {'a',  1}, 
                                {'b',  2}, 
                                {'c',  3}, 
                                {'c',  4}, 
                                {'d',  5}, 
                                {'c',  6}, 
                                {'e',  7}, 
                            };

    // print total elements with key = 'c'
    auto result = charPositionMap.equal_range('c');
    int count = std::distance( result.first, result.second );
    std::cout << std::endl << "\nTotal Keys for 'c': " << count << std::endl;

    // print all elements for key='c':  should print 6,4,3 for example above

    // Print All Elements: METHOD #1 - Naive
    // for(auto it = result.first; it!=result.second; it++){
    //     std::cout<< it->first << " , " << it->second <<std::endl;
    // }

    // Print All Elements: METHOD #2 - Stl algorithms & C++11
    // auto print = []( std::pair< const char, int>& pair){ 
    //     std::cout<< pair.first << " , " << pair.second <<std::endl; 
    // };
    
    // Print All Elements: METHOD #3 - Stl algorithms & C++14
    auto lambda = [&](const auto & p){
        std::cout<< p.first << " , " << p.second <<std::endl; 
    };

    std::for_each( result.first, result.second, lambda);

    return 0;
}
