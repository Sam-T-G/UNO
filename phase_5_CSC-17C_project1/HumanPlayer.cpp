#include "HumanPlayer.h"
#include <iostream>

HumanPlayer::HumanPlayer()
{
    role = "HUMAN";
}

void HumanPlayer::disPrvSts() const
{
    cout << "[HUMAN DEBUG] Max Combo: " << getMaxCombo() << ", Turns: " << trns << endl;
}
