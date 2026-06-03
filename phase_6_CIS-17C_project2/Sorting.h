#ifndef SORTING_H
#define SORTING_H
#include <cstddef>
using namespace std;

// Working-pair data for merge sort. sortit holds the array being sorted,
// working is a pre-allocated buffer the merge step writes into and copies
// back from, which avoids per-recursion-frame allocations.
struct Data
{
    int size;
    int *sortit;
    int *working;
};

// Merge sort: recursive split, then merge through the working buffer.
void mrgSort(Data *, int beg, int end);

// Merge two sorted halves [beg, nlow) and [nlow, nhigh).
void merge(Data *, int beg, int nlow, int nhigh);

// Quick sort with Hoare partition.
void qkSort(int *, int lo, int hi);

// Hoare partition. Returns the partition index for qkSort recursion.
int partition(int *, int lo, int hi);

#endif
