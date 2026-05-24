#include "NPCPlayer.h"

extern void npcTrn(Player &, Player &, Card &, bool &);

NPCPlayer::NPCPlayer()
{
    role = "NPC"; // accesses protected member in Player
}

void NPCPlayer::printRole() const
{
    cout << name << " is a " << role << " player.\n";
}

void NPCPlayer::takeTurn(Player &opponent, Card &actvCrd, bool &turn)
{
    npcTrn(opponent, *this, actvCrd, turn);
}

// SAVE FOR FUTURE IMPLEMENTATION
//  void NPCPlayer::disPrvSts() const
//  {
//      cout << "[NPC DEBUG] Max Combo: " << getMaxCombo() << ", Turns: " << trns << endl;
//  }
