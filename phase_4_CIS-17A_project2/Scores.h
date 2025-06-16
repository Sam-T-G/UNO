#ifndef SCORES_H
#define SCORES_H

struct Scores
{
    int trns;
    int cmbHi;
};

template <typename T>
T maxValue(T a, T b)
{
    return (a > b) ? a : b;
}

#endif
