#ifndef CARD_H
#define CARD_H

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
};

#endif
