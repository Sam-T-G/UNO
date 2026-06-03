#ifndef EFFECT_CHAIN_H
#define EFFECT_CHAIN_H

#include <string>
#include <vector>
#include "Card.h"
#include "Player.h"
using namespace std;

const int MAX_STACK = 4;

struct EffectAccum
{
    int drawCount;
    bool skipTarget;
    int chainLen;
    vector<string> log;
};

bool isStackable(const Card &c);

// Recursive resolver for stackable effect cards (SKIP, DRAW_TWO, DRAW_FOUR).
// stacker is the player whose hand the resolver peeks for a chain card; the
// chained card is consumed from stacker.hand. The effect target (who draws or
// loses a turn) is the caller's responsibility to apply from the accumulator.
void resolveEffect(Card played, Player &stacker, int depth, EffectAccum &acc);

#endif
