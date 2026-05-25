#ifndef NPCPLAYER_H
#define NPCPLAYER_H

#include "Player.h"
#include <iostream>
using namespace std;

class NPCPlayer : public Player // NPC player is a derived Class
{
public:
    NPCPlayer(); // Constructor

    void printRole() const;
    void takeTurn(Player &opponent, stack<Card> &discard, queue<Card> &deck, bool &turn) override;
    void disPrvSts() const override;
};

#endif
