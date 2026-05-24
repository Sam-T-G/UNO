#ifndef CARD_H
#define CARD_H
#include <iostream> // Required for ostream
using namespace std;

enum CardClr
{
    RED,
    BLUE,
    YELLOW,
    GREEN,
    WILD
};
enum CardSuit
{
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    SKIP,
    DRAW_TWO,
    DRAW_FOUR
};

struct Card
{
    CardClr color;
    CardSuit suit;

    static int totalDrawn; // Static member declaration
};

// Operator Overload Prototypes
bool operator==(const Card &, const Card &);
ostream &operator<<(ostream &, const Card &);

#endif
