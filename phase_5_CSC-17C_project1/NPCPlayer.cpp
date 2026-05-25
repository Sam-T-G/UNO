#include "NPCPlayer.h"
#include <stack>
#include <queue>

extern void npcTrn(Player &, Player &, stack<Card> &, queue<Card> &, bool &);

NPCPlayer::NPCPlayer()
{
    role = "NPC"; // accesses protected member in Player
}

void NPCPlayer::printRole() const
{
    cout << name << " is a " << role << " player.\n";
}

void NPCPlayer::takeTurn(Player &opponent, stack<Card> &discard, queue<Card> &deck, bool &turn)
{
    npcTrn(opponent, *this, discard, deck, turn);
}

// SAVE FOR FUTURE IMPLEMENTATION
//  void NPCPlayer::disPrvSts() const
//  {
//      cout << "[NPC DEBUG] Max Combo: " << getMaxCombo() << ", Turns: " << trns << endl;
//  }
