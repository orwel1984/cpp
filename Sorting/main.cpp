//
//  main.cpp
//  Sorting
//
//  Created by tanweer ali on 28/05/2021.
//

#include <iostream>
#include <vector>
#include <string>

//----------------------------------------------------
// Debug Function
//----------------------------------------------------

template <typename T>
void PrintArray(std::vector<T>& v)
{
    std::cout<< "\n";
    
    for(auto elem: v){
        std::cout<< elem <<" , ";
    }
    
    std::cout<< "\n";
}

//----------------------------------------------------
// Bubble Sort
//----------------------------------------------------

template <typename T>
bool BubbleSort_Scan(std::vector<T>& v, int N)
{
    bool swapped = false;       // a flag to indicate if swapping happened or not.
    for(int i=0; i<N-1; i++){
        // compare adjacent elements
        if( v[i] > v[i+1] ){
            std::swap(v[i], v[i+1]);
            swapped = true;
        }
    }
    return swapped;
}

template <typename T>
void BubbleSort(std::vector<T>& v)
{
    int N = static_cast<int>(v.size());
    for( ; N>0; N--){
        if( !BubbleSort_Scan(v, N) )  // nothing swapped? then list is already sorted
            break;
    }
}

//----------------------------------------------------
// Insertion Sort
//----------------------------------------------------

/* Function to sort an array using insertion sort*/
template <typename T>
void InsertionSort(std::vector<T>& v)
{
    for (int i = 1; i < v.size(); i++)
    {
        int key = v[i];
        int j= i-1;

        /* Move all elements (v[i-1] > key) , to right j+1 */
        for( ; (j>=0 && v[j]>key) ; --j)
        {
            v[j+1] = v[j];
        }
        
        // now copy the key to the location after (v[j] < key)
        v[j+1] = key;
    }
}

//----------------------------------------------------
// Merge Sort
//----------------------------------------------------
// Worst Case Time Complexity : O(n*log n)
// Best Case Time Complexity  : O(n*log n)
// Average Time Complexity    : O(n*log n)
// Space Complexity           : O(n)


// prototypes
template <typename T> void MergeSort(std::vector<T>& a, std::vector<T>& b, int s, int e);
template <typename T> void Merge(std::vector<T>& v, std::vector<T>& b, int start, int mid, int end);

template <typename T>
void MergeSortAlgo(std::vector<T>& v)
{
    const int N = static_cast<const int>(v.size());
    
    std::vector<T> b(N);       // a temporary array for merge results
    
    MergeSort(v, b, 0, N-1);
}

template <typename T>
void MergeSort(std::vector<T>& a, std::vector<T>& b, int start, int end)
{
    int mid;
    int low = start;
    int high = end;
    if(low < high) {
       mid = (start + end) / 2;
       MergeSort(a, b, low, mid);
       MergeSort(a, b, mid+1, high);
       Merge(a, b, low, mid, high);
    } else {
       return;
    }
}

template <typename T>
void Merge(std::vector<T>& v,
           std::vector<T>& b,
           int start, int mid, int end)
{
    int l = start;  // left-array index
    int r = mid+1;  // right-array index
    
    int i = start;  // result-array b index

    // compare both aarays on left & right,
    // and copy the smallest element into final array b
    // and increment the indices l or r and i
    while( l<=mid && r<=end){
        if( v[l] <= v[r]){
            b[i++] = v[l++];
        }
        else if( v[r] < v[l]){
            b[i++] = v[r++];
        }
    }
    
    // copy remaining leftover elements from left-array, if any
    while(l<=mid){
        b[i++] = v[l++];
    }
    
    // copy remaining leftover elements from right-array, if any
    while(r<=end){
        b[i++] = v[r++];
    }

    // final copy into destination array
    for(int j=start; j<=end; j++){
        v[j] = b[j];
    }
    
}

//----------------------------------------------------
// Quick Sort
//----------------------------------------------------
// Worst Case Time Complexity : O(n*n)
// Best Case Time Complexity  : O(n*log n)
// Average Time Complexity    : O(n*log n)
// Space Complexity           : O(1)
template <typename T>
int Partition(std::vector<T>& v, int low, int high)
{
    for(; low!=high; ){
        
        if(v[low]>v[high]){
            std::swap(v[low],v[high]);
            ++high;  // increment Right pointer after swap
        }
        else{
            ++low;  // increment Left pointer after no-swap
        }
    }
    return low;
}

template <typename T>
void QuickSort(std::vector<T>& v, int low, int high)
{
    if(low < high){
        int pivot = Partition(v, low, high);
        QuickSort(v, low,     pivot-1);
        QuickSort(v, pivot+1, high );
    } else{
        return;
    }
}
//----------------------------------------------------
// Rough

//// C++17 fold expression
//template <typename ... T>
//auto sum(const T& ... x) {
//  return (x + ...);
//}

// C++14 - no fold expressions
// This is the standard technique for unraveling the parameter packs in variadic templates
template <typename T1>
auto sum(const T1& x1) {
   return x1;
}

template <typename T1, typename ... T>
auto sum(const T1& x1, const T& ... x) {
   return x1 + sum(x ...);
}

//-----------------------------------------------------

template <typename ... T>
   struct Group;

template <typename T1>
   struct Group<T1> {
       T1 t1_;
       Group() = default;
       explicit Group(const T1& t1) : t1_(t1) {}
       explicit Group(T1&& t1) : t1_(std::move(t1)) {}
       explicit operator const T1&() const { return t1_; }
       explicit operator T1&() { return t1_; }
};

template <typename T1, typename ... T>
   struct Group<T1, T ...> : Group<T ...> {
       T1 t1_;
       Group() = default;
       explicit Group(const T1& t1, T&& ... t)
                    : Group<T ...>(std::forward<T>(t) ...), t1_(t1) {}
       explicit Group(T1&& t1, T&& ... t)
                    : Group<T ...>(std::forward<T>(t) ...), t1_(std::move(t1)) {}
       explicit operator const T1&() const { return t1_; }
       explicit operator T1&() { return t1_; }
};

template <typename ... T>
auto makeGroup(T&& ... t) {
   return Group<T ...>(std::forward<T>(t) ...);
}
//----------------------------------------------------
int main(int argc, const char * argv[]) {
    
    std::vector<int> v = {2,5,10,1,43,25,18,6,4,3,45, 33, 37, 21, 11, 23, 22, 49, 34, 100};
    
    auto copy = v; // make a copy of the above vector to try different algorithms
    
    BubbleSort(v);
    PrintArray(v);
    
    v = copy;
    InsertionSort(v);
    PrintArray(v);
    
    v = copy;
    MergeSortAlgo(v);
    PrintArray(v);

    v = copy;
    QuickSort(v, 0, static_cast<int>(v.size())-1 );
    PrintArray(v);

    std::cout   << std::endl
                <<sum(1,2,3,4,5,6,7)
                << std::endl;
    
    auto g = makeGroup(3, 2.2, std::string("xyz"));
    std::cout<< std::endl <<static_cast<std::string>(g) << std::endl ;
    
    return 0;
}
