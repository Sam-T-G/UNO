#include "EffectChain.h"
#include <list>
using namespace std;

bool isStackable(const Card &c)
{
    return c.suit == SKIP || c.suit == DRAW_TWO || c.suit == DRAW_FOUR;
}

static list<Card>::iterator findStackable(list<Card> &hand)
{
    for (auto it = hand.begin(); it != hand.end(); ++it)
    {
        if (isStackable(*it))
        {
            return it;
        }
    }
    return hand.end();
}

static void applyEffect(const Card &played, EffectAccum &acc)
{
    if (played.suit == SKIP)
    {
        acc.skipTarget = true;
        acc.log.push_back("SKIP applied!");
    }
    else if (played.suit == DRAW_TWO)
    {
        acc.drawCount += 2;
        acc.log.push_back("DRAW 2 applied!");
    }
    else if (played.suit == DRAW_FOUR)
    {
        acc.drawCount += 4;
        acc.log.push_back("DRAW 4 applied!");
    }
}

void resolveEffect(Card played, Player &stacker, int depth, EffectAccum &acc)
{
    //Base Condition: a non-effect card contributes nothing to the chain
    if (!isStackable(played))
    {
        return;
    }
    //Base Condition: depth cap prevents runaway recursion
    if (depth >= MAX_STACK)
    {
        return;
    }

    applyEffect(played, acc);
    acc.chainLen = depth + 1;

    //Recursion: peek the stacker's hand for a chainable card and consume it
    auto next = findStackable(stacker.hand);
    if (next != stacker.hand.end())
    {
        Card chained = *next;
        stacker.hand.erase(next);
        resolveEffect(chained, stacker, depth + 1, acc);
    }
}
