/*
Name: Samuel Gerungan
Date: 6/2/26
Purpose: Timing study driver for mrgSort and qkSort from Sorting.h.
         Times each over a range of N and writes plot files.
         Build: g++ -std=c++17 -DSORT_STUDY Sorting.cpp sorting_study.cpp -o sort_study
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Sorting.h"
using namespace std;

// Wide N range so the timing curve shows the full progression from near-zero
// to large gap between the two sorts.
const int NSIZE = 9;
const int SIZES[NSIZE] = {1000000, 2000000, 4000000, 8000000, 16000000,
                          32000000, 64000000, 128000000, 256000000};

Data *fill(int);
void destroy(Data *);
int mkRndS();
void writeFit(const char *, int, const int *, const int *);

int main(int argc, char **argv)
{
    srand(static_cast<unsigned int>(time(0)));

    int tQk[NSIZE];
    int tMr[NSIZE];

    cout << "N\tQSort\tMerge  (seconds)" << endl;

    for (int s = 0; s < NSIZE; s++)
    {
        int n = SIZES[s];

        Data *a = fill(n);
        int beg = time(0);
        qkSort(a->sortit, 0, n - 1);
        tQk[s] = time(0) - beg;
        destroy(a);

        a = fill(n);
        beg = time(0);
        mrgSort(a, 0, a->size);
        tMr[s] = time(0) - beg;
        destroy(a);

        cout << n << "\t" << tQk[s] << "\t" << tMr[s] << endl;
    }

    writeFit("quick_time.txt", NSIZE, SIZES, tQk);
    writeFit("merge_time.txt", NSIZE, SIZES, tMr);

    return 0;
}

// Allocate a Data block with n random ints in sortit and an n-sized working
// buffer for merge to stage rebuilt halves into.
Data *fill(int n)
{
    Data *data = new Data;
    data->size = n;
    data->sortit = new int[n];
    data->working = new int[n];
    for (int i = 0; i < n; i++)
    {
        data->sortit[i] = mkRndS();
    }
    return data;
}

void destroy(Data *a)
{
    delete[] a->sortit;
    delete[] a->working;
    delete a;
}

// 4-byte random int built by shifting one 16-bit rand into the high half and
// adding a second 16-bit rand for the low half. rand() alone caps at 15 bits.
int mkRndS()
{
    int temp = rand();
    temp <<= 16;
    return temp + rand();
}

// Write a curve_fit input: count on line 1, X row on line 2, Y row on line 3.
// Format mirrors the Lehr Recursions and Sorts lab plot file exactly.
void writeFit(const char *name, int n, const int *x, const int *y)
{
    ofstream fout(name);
    fout << n << "\n";
    for (int i = 0; i < n; i++)
    {
        fout << x[i] << " ";
    }
    fout << "\n";
    for (int i = 0; i < n; i++)
    {
        fout << y[i] << " ";
    }
    fout << "\n";
}
