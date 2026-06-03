#ifndef CARD_H
#define CARD_H
#include <iostream> // Required for ostream
#include <cstddef>  // Required for size_t
#include <functional> // Required for std::hash
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

    // rubric: static int totalDrawn (Ch.13.6)
    static int totalDrawn; // Static member declaration
};

// Operator Overload Prototypes
bool operator==(const Card &, const Card &);
bool operator<(const Card &, const Card &); // total ordering on Card
ostream &operator<<(ostream &, const Card &);

// std::hash specializations must live in namespace std.
namespace std
{
    template <>
    struct hash<CardClr>
    {
        size_t operator()(const CardClr &c) const noexcept
        {
            return static_cast<size_t>(c);
        }
    };

    template <>
    struct hash<Card>
    {
        size_t operator()(const Card &c) const noexcept
        {
            // BKDR multiplicative hash, seed 131.
            size_t h = 0;
            h = h * 131 + static_cast<size_t>(c.color);
            h = h * 131 + static_cast<size_t>(c.suit);
            return h;
        }
    };
}

#endif
