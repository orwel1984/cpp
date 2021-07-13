//
//  main.cpp
//  Sorting
//
//  Created by tanweer ali on 28/05/2021.
//

#include <iostream>
#include <vector>
#include <string>

/*
    Complexity:

    Algorithm complexity could mean two things.

    1.  Time complexity.
    2.  Space complexity.

    It is denoted by the following symbols:

    O() is the upper bound or worst-case scenario. Also called Big-O. 
    Ω() is the lower bound or the best-case scenario.
    Θ() is the avergae case

    O(1):   Complexity does'nt change with input size. 
            It remains constant regardless of the input.
            e.g. accessing an Array[i] is O(1) operation.
            Same applies to std::map[key].

    O(N):   Complexity grows linearly with the input size.
            Usually the case of a single for-loop

    O(N^2): Complexity grows linearly with the input size.
            Usually the case with two nested for-loops            

    O(logN):    Complexity grows at log(N) rate. 
                This is the case with divide-n-conquer or 
                Binary Searching or Binary Trees             

*/ 


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
// Selection Sort
//----------------------------------------------------
//
// Simplest sort to think about.
// 
// Goes over all elements of the array A[i] from i=[0, N-1]
// and compare each element with all the rest for 
// being the smallest. 
// 
// if A[i] < A[k] for k=[i=1, N-1] then
// swap(A[i], A[k]) is called. And then the loop contiues as 
// normal for the rest of the loop k.
// 
// If the list is already sorted, the algorithm does'nt care.
// It's very naive.
// It does N^2 comparisons.
// 
// Complexity:
// Worst Case Time Complexity : O(N^2)
// Space Complexity           : O(1)
//----------------------------------------------------


//----------------------------------------------------
// Bubble Sort: 
//----------------------------------------------------
//
// Goes over all elements of the array A[i] from i=[0, N-1]
// checks if v[i] > v[i+1] then swap(v[i], v[i+1])
// ( it only checks the adjacent elements.
// 
// After going over the entire list once, the largest element 
// in the list pops-out (or bubbles out) at the right-end 
// of the list. This step is called Scan(N).
// 
// Repeat the Scan step above for for N-1 remaining members i.e.  
// Scan(N-1) and so on.
// 
// If the list is already sorted, then nothing is swapped 
// and we can break-out of the algorithm early.
// ( So we say that the Bubble-Sort is an "Adaptive" algorithm )
//
// Complexity:
// Time Complexity : O(N^2)
// Space Complexity: O(1)
//
// No. of comparisons: O(N^2) 
// No. of swaps: O(N^2) 
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
// Insertion Sort:
//----------------------------------------------------
// Starts initially with the first element A[0]
// and assumes it is sorted sublist. 
// 
// It then adds second element A[1] to that and sorts 
// them if needed. 
// So the sublist size grows but it remains sorted.
// And highest element of this sublist is always rightmost.
// 
// Repeats the same process for A[2]...A[N] and compares
// each new item with the largest element of the sublist.
// If the new element is smaller then it is swapped, and compared
// with all remaning elements of sublist until no more swaps are 
// needed.
//
// Problems with this:
// The worst case happens when each new element A[i] to be added 
// to the sublist is smallest element. Then it needs to be swapped
// over to the leftmost position by moving over all the elements
// of the sublist.
// 
// It is also a Stable-sort and is also Adaptive.
// It does fewer comparisons and swaps than Bubble-sort on average.
// 
// Complexity:
// Time Complexity : O(N^2)
// Space Complexity: O(1)
//
//----------------------------------------------------

/* Function to sort an array using insertion sort*/
template <typename T>
void InsertionSort(std::vector<T>& A)
{
    int N = A.size();
    for (int i = 0; i <N-1; ++i)
    {
        for (int j=i+1; j>0; --j)
        {
            if(A[j] < A[j-1]){
                std::swap(A[j] , A[j-1]);
            } else{
                break;
            }
        }
    }

}

//----------------------------------------------------
// Merge Sort
//----------------------------------------------------
// 
// Recursively subdivides the list until it reaches only one element in sublist.
// Then it merges these small sublists together in sorted manner.
//
// It uses extra space of N elements to build up the sorted merged list.
// This means that it requires O(N) extra space which linearly grows with problem size N.
//
// It is not an Adaptive method and will try to sort an already sorted list.
// It is a Stable sorting method, thus the order of elements is preserved if they are equal.
// 
// Worst Case Time Complexity : O(N*log N)
// Best Case Time Complexity  : O(N*log N)
// Average Time Complexity    : O(N*log N)
// Space Complexity           : O(N)

// prototypes
template <typename T> void Split(std::vector<T>& a, std::vector<T>& b, int s, int e);
template <typename T> void Merge(std::vector<T>& v, std::vector<T>& b, int start, int mid, int end);

template <typename T>
void MergeSortAlgo(std::vector<T>& v)
{
    const int N = static_cast<const int>(v.size());    
    std::vector<T> b(N);   // a temporary array for merge results
    
    Split(v, b, 0, N-1);   // Split will start to recursively split list
}

template <typename T>
void Split( std::vector<T>& A, 
            std::vector<T>& B, 
            int start, 
            int end )
{
    if(start < end) 
    {
       int mid = (start + end) / 2;
       Split(A, B,  start,  mid);
       Split(A, B,  mid+1,  end);
       Merge(A, B,  start,  mid, end);
    } 
    else {      // start == end
       return;  //recursion terminate condition
    }
}

template <typename T>
void Merge(std::vector<T>& A,
           std::vector<T>& B,
           int start, int mid, int end)
{
    int l = start;  // left-array index
    int r = mid+1;  // right-array index
    
    int b = start;  // result-array B index

    // compare both arrays on left & right,
    // and copy the smallest element into final array b
    // and increment the indices l or r and i
    while( l<=mid && r<=end){
        if( A[l] <= A[r]){
            B[b++] = A[l++];
        }
        else if( A[r] < A[l]){
            B[b++] = A[r++];
        }
    }
    
    // copy leftover elements from left-array, if any
    while(l<=mid){
        B[b++] = A[l++];
    }
    
    // copy leftover elements from right-array, if any
    while(r<=end){
        B[b++] = A[r++];
    }

    // final copy into destination array
    for(int j=start; j<=end; j++){
        A[j] = B[j];
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

    return 0;
}
