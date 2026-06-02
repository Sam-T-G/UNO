#include "Sorting.h"

// Recursive merge sort, split the task down the middle.
void mrgSort(Data *a, int beg, int end)
{
    int center = (beg + end) / 2;
    if ((center - beg) > 1)
    {
        mrgSort(a, beg, center);
    }
    if ((end - center) > 1)
    {
        mrgSort(a, center, end);
    }
    merge(a, beg, center, end);
}

// Merge two sorted halves through the working buffer, then copy back.
void merge(Data *a, int beg, int nlow, int nhigh)
{
    int span = nhigh - beg;
    int cntl = beg;
    int cnth = nlow;
    for (int i = 0; i < span; i++)
    {
        if (cntl == nlow)
        {
            a->working[i] = a->sortit[cnth++];
        }
        else if (cnth == nhigh)
        {
            a->working[i] = a->sortit[cntl++];
        }
        else if (a->sortit[cntl] < a->sortit[cnth])
        {
            a->working[i] = a->sortit[cntl++];
        }
        else
        {
            a->working[i] = a->sortit[cnth++];
        }
    }
    for (int i = 0; i < span; i++)
    {
        a->sortit[beg + i] = a->working[i];
    }
}

// Quick sort, Hoare partition, recursive on each side.
void qkSort(int *a, int lo, int hi)
{
    if (lo < hi)
    {
        int p = partition(a, lo, hi);
        qkSort(a, lo, p);
        qkSort(a, p + 1, hi);
    }
}

// Hoare partition. Pivot is the middle element; converging i / j
// indices swap out-of-place values until they cross.
int partition(int *a, int lo, int hi)
{
    int pivot = a[(lo + hi) / 2];
    int i = lo - 1;
    int j = hi + 1;
    while (true)
    {
        do
        {
            i++;
        } while (a[i] < pivot);
        do
        {
            j--;
        } while (a[j] > pivot);
        if (i >= j)
        {
            return j;
        }
        int t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
}
