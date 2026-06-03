#ifndef SCORES_H
#define SCORES_H

struct Scores
{
    int trns;
    int cmbHi;
};

// rubric: template maxValue<T> (Ch.16.2)
template <typename T>
T maxValue(T a, T b)
{
    return (a > b) ? a : b;
}

#endif
