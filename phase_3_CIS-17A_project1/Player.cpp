#include "Player.h"
#include "Card.h"

extern Card draw();

void Player::rstCmb()
{
    cmb = 0;
}

void Player::updCmb()
{
    cmb++;
    if (cmb > cmbMx)
        cmbMx = cmb;
}

void Player::drwCrd()
{
    hand.push_back(draw());
}

int Player::hndSze() const
{
    return hand.size();
}
