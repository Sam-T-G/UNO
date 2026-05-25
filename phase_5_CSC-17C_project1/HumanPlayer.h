#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player
{
public:
    HumanPlayer();
    void disPrvSts() const override;
};

#endif
