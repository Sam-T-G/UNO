#include "NPCPlayer.h"

NPCPlayer::NPCPlayer()
{
    role = "NPC"; // accesses protected member in Player
}

void NPCPlayer::printRole() const
{
    cout << name << " is a " << role << " player.\n";
}

// void NPCPlayer::takeTurn(Player &opponent, Card &actvCrd, bool &turn) {
//     npcTrn(opponent, *this, actvCrd, turn); // Use existing npcTrn()
// }
