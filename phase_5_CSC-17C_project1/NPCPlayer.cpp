#include "NPCPlayer.h"
#include <stack>

extern void npcTrn(Player &, Player &, std::stack<Card> &, bool &);

NPCPlayer::NPCPlayer()
{
    role = "NPC"; // accesses protected member in Player
}

void NPCPlayer::printRole() const
{
    cout << name << " is a " << role << " player.\n";
}

void NPCPlayer::takeTurn(Player &opponent, std::stack<Card> &discard, bool &turn)
{
    npcTrn(opponent, *this, discard, turn);
}

// SAVE FOR FUTURE IMPLEMENTATION
//  void NPCPlayer::disPrvSts() const
//  {
//      cout << "[NPC DEBUG] Max Combo: " << getMaxCombo() << ", Turns: " << trns << endl;
//  }
